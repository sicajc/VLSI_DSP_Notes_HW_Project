module GR #(
    parameter D_WIDTH = 4,
    parameter DATA_WIDTH = 20,
    parameter Q_GR = 0,
    parameter R_GR = 1
  ) (
    input clk,
    input rst_n,

    input signed[DATA_WIDTH-1:0] a_ij,     //a_ij is the input of GRs for propogating signals
    input signed[D_WIDTH-1:0] d_i,
    input rotates_i,
    input valid_i,
    input clr_i,

    //output register or GR
    output reg signed[DATA_WIDTH-1:0] rij_ff_o,
    output reg signed[DATA_WIDTH-1:0] x_ff,
    output reg signed[DATA_WIDTH-1:0] y_ff,
    output reg valid_d_o,
    output reg rotates_d_o,
    // To propogate rotation dis to another GRs
    output reg [D_WIDTH-1:0] d_i_d_o
  );
  // GR would sends out valid signal only after two full rotations
  // GR (x,y) -> (x',y'), where y' would be send out to the next GR or GG; while x would replace the current y stays in thus GR.

  //===============================
  //   PARAMETERS
  //===============================
  parameter K = 20'b0000000000_1001101101;
  // I:10, F:10
  genvar idx;

  //===============================
  //   MULT AND CORDIC
  //===============================
  wire signed[DATA_WIDTH-1:0] iters_x_in;
  wire signed[DATA_WIDTH-1:0] iters_y_in;
  wire signed[DATA_WIDTH*2-1:0] K_product_x;
  wire signed[DATA_WIDTH*2-1:0] K_product_y;
  wire signed[DATA_WIDTH-1:0] K_extracted;

  reg signed[DATA_WIDTH-1:0] iters_x[0:3];
  reg signed[DATA_WIDTH-1:0] iters_y[0:3];

  //===============================
  //   CONTROL
  //===============================
  reg[1:0] cnt;
  reg Twice_f;
  reg Working_f;

  wire iters_done_f  = cnt == 2;
  wire gr_done_f     = cnt == 3;
  wire iters_start_f = cnt == 0 && valid_i;
  wire gr_in_work_f  = Working_f || valid_i;
  wire done_twice_f  = Twice_f && gr_done_f; // Check if I have done two rotations

  always @(posedge clk or negedge rst_n)
  begin
    if(~rst_n)
    begin
      Working_f   <= 0;
      valid_d_o   <= 0;
      Twice_f <= 0;
    end
    else if(clr_i)
    begin
      Working_f   <= 0;
      valid_d_o   <= 0;
      Twice_f <= 0;
    end
    else if(gr_done_f)
    begin
      Working_f   <= 0;

      if(done_twice_f)
      begin
        valid_d_o   <= 1;
      end
      else
      begin
        valid_d_o   <= 0;
      end
      Twice_f <= 1;
    end
    else if(valid_i)
    begin
      Working_f   <= 1;
      valid_d_o   <= 0;
      Twice_f <= Twice_f;
    end
    else
    begin
      Working_f <= Working_f;
      valid_d_o <= 0;
      Twice_f <= Twice_f;
    end
  end

  always @(posedge clk or negedge rst_n)
  begin
    if(~rst_n)
    begin
      rotates_d_o <= 0;
    end
    else if(clr_i)
    begin
      rotates_d_o <= 0;
    end
    else
    begin
      rotates_d_o <= rotates_i;
    end
  end

  always @(posedge clk or negedge rst_n)
  begin
    if(~rst_n)
    begin
      cnt <= 0;
    end
    else if(clr_i||gr_done_f)
    begin
      cnt <= 0;
    end
    else if(gr_in_work_f)
    begin
      cnt <= cnt + 1;
    end
    else
    begin
      cnt <= cnt;
    end
  end

  always @(posedge clk)
  begin
    if(!rst_n)
    begin
      x_ff <= 0;
      y_ff <= 0;
      rij_ff_o <= 0;
    end
    else if(clr_i)
    begin
      x_ff <= 0;
      y_ff <= 0;
      rij_ff_o <= 0;
    end
    else if(gr_done_f)
    begin
      x_ff     <= x_ff;
      if(R_GR == 1)
      begin
        y_ff     <= $signed({K_product_x[39],K_product_x[28:10]});
        rij_ff_o <= $signed({K_product_y[39],K_product_y[28:10]});
      end
      else
      begin
        y_ff     <= $signed({K_product_x[23],K_product_x[20:10]});
        rij_ff_o <= $signed({K_product_y[23],K_product_y[20:10]});
      end
    end
    else if(gr_in_work_f && rotates_i)
    begin
      x_ff <= iters_x[3];
      y_ff <= iters_y[3];
      rij_ff_o <= rij_ff_o;
    end
    else
    begin
      x_ff <= x_ff;
      y_ff <= y_ff;
      rij_ff_o <= rij_ff_o;
    end
  end

  assign K_product_x = $signed(x_ff) * $signed(K);
  assign K_product_y = $signed(y_ff) * $signed(K);
  assign K_extracted = {K_product_x[39],K_product_x[28:10]};

  assign iters_x_in = iters_start_f ? a_ij : x_ff;
  assign iters_y_in = y_ff;

  generate
    for ( idx=0; idx<4; idx=idx+1)
    begin
      always @(*)
      begin
        if(idx == 0)
        begin
          if(d_i[0]==0)
          begin
            iters_x[0] = iters_x_in + (iters_y_in >>> (cnt*4 + 0));
            iters_y[0] = iters_y_in - (iters_x_in >>> (cnt*4 + 0));
          end
          else
          begin
            iters_x[0] = iters_x_in - (iters_y_in >>> (cnt*4 + 0));
            iters_y[0] = iters_y_in + (iters_x_in >>> (cnt*4 + 0));
          end
        end
        else
        begin
          if(d_i[idx]==0)
          begin
            iters_x[idx] = iters_x[idx-1] + (iters_y[idx-1] >>> (cnt*4 + idx));
            iters_y[idx] = iters_y[idx-1] - (iters_x[idx-1] >>> (cnt*4 + idx));
          end
          else
          begin
            iters_x[idx] = iters_x[idx-1] - (iters_y[idx-1] >>> (cnt*4 + idx));
            iters_y[idx] = iters_y[idx-1] + (iters_x[idx-1] >>> (cnt*4 + idx));
          end
        end
      end
    end

    for ( idx = 0; idx<4; idx = idx+1)
    begin
      always @(posedge clk or negedge rst_n)
      begin
        if(~rst_n)
        begin
          d_i_d_o[idx] <= 0;
        end
        else
        begin
          d_i_d_o[idx] <= d_i[idx];
        end
      end
    end
  endgenerate



endmodule
