module GR #(
    parameter D_WIDTH = 4,
    parameter DATA_WIDTH = 20
) (
    input clk,
    input rst_n,

    input signed[DATA_WIDTH-1:0] a_ij,
    input signed[D_WIDTH-1:0] d_i,
    input rotates_i,
    input valid_i,
    input propogate_i,

    output reg signed[DATA_WIDTH-1:0] rij_ff_o,
    output reg valid_d_o,
    output reg propogate_d_o,
    output reg rotates_d_o,
    output reg [D_WIDTH-1:0] d_i_d_o
);

parameter K = 20'b0000000000_1001101101;
// I:10, F:10
genvar idx;

reg signed[DATA_WIDTH-1:0] x_ff,y_ff;
reg working_f;

wire signed[DATA_WIDTH-1:0] iters_x_in;
wire signed[DATA_WIDTH-1:0] iters_y_in;
wire signed[DATA_WIDTH*2-1:0] K_product_x;
wire signed[DATA_WIDTH-1:0] K_extracted;

reg signed[DATA_WIDTH-1:0] iters_x[0:3];
reg signed[DATA_WIDTH-1:0] iters_y[0:3];

reg[1:0] cnt;
wire iters_done_f  = cnt == 2;
wire gr_done_f     = cnt == 3;
wire iters_start_f = cnt == 0 && valid_i;
wire gr_in_work_f  = working_f || valid_i;

 always @(posedge clk or negedge rst_n)
  begin
    if(~rst_n)
    begin
      working_f   <= 0;
      valid_d_o   <= 0;
    end
    else if(propogate_i)
    begin
      working_f   <= working_f;
      valid_d_o   <= 1;
    end
    else if(gr_done_f)
    begin
      working_f <= 0;
      valid_d_o   <= 1;
    end
    else if(valid_i)
    begin
      working_f   <= 1;
      valid_d_o   <= 0;
    end
    else
    begin
      working_f <= working_f;
      valid_d_o <= 0;
    end
  end

  always @(posedge clk or negedge rst_n)
  begin
    if(~rst_n)
    begin
      rotates_d_o <= 0;
      propogate_d_o <= 0;
    end
    else
    begin
      rotates_d_o <= rotates_i;
      propogate_d_o <= propogate_i;
    end
  end

  always @(posedge clk or negedge rst_n)
  begin
     if(~rst_n)
    begin
      cnt <= 0;
    end
    else if(propogate_i)
    begin
      cnt <= cnt;
    end
    else if(gr_done_f)
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

always @(posedge clk) begin
    if(!rst_n)
    begin
        x_ff <= 0;
        y_ff <= 0;
        rij_ff_o <= 0;
    end
    else if(propogate_i)
    begin
      x_ff <= x_ff;
      y_ff <= y_ff;
      rij_ff_o <= a_ij;
    end
    else if(gr_done_f)
    begin
      x_ff     <= x_ff;
      y_ff     <= $signed({K_product_x[39],K_product_x[28:10]});
      rij_ff_o <= $signed({K_product_x[39],K_product_x[28:10]});
    end
    else if(gr_in_work_f)
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
assign K_extracted = {K_product_x[39],K_product_x[28:10]};

assign iters_x_in = iters_start_f ? a_ij : x_ff;
assign iters_y_in = y_ff;

generate
for ( idx=0; idx<4; idx=idx+1) begin
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