`define GGR2OUTPUT 18:7
module QR_CORDIC #(
    parameter D_WIDTH = 4,
    parameter DATA_WIDTH = 20,
    parameter INPUT_DATA_WIDTH = 8,
    parameter R_DATA_WIDTH = 20,
    parameter Q_DATA_WIDTH = 12
  ) (
    input clk,
    input rst_n,

    input in_valid,
    input signed[INPUT_DATA_WIDTH-1:0] in,

    output reg out_valid,
    output reg signed[Q_DATA_WIDTH-1:0] out_r,
    output reg signed[Q_DATA_WIDTH-1:0] out_q
  );
  //===============================
  //   PARAMETERS & GENVARS
  //===============================
  parameter GG_NUM   = 3;
  parameter R_GR_NUM = 6;
  parameter Q_GR_NUM = 12;

  genvar i,j,k;

  //===============================
  //   FSM
  //===============================
  parameter IDLE    = 5'b00001;
  parameter RD_DATA = 5'b00010;
  parameter CAL     = 5'b00100;
  parameter OUTPUT  = 5'b01000;

  reg[4:0] current_state,next_state;

  wire state_IDLE    = current_state == IDLE;
  wire state_RD_DATA    = current_state == RD_DATA;
  wire state_CAL    = current_state == CAL;
  wire state_OUTPUT    = current_state == OUTPUT;
  //===============================
  //   CNT
  //===============================
  reg[8:0] cordic_cnt;
  //===============================
  //   4xFIFO
  //===============================
  reg[R_DATA_WIDTH-1:0] aij_shift_bufs[0:3][0:3];
  reg[3:0] qij_bufs[0:3];
  //===============================
  //   Valid Delays line
  //===============================
  reg[8:0] valid_delay_line_ff;

  //===============================
  //   GGs
  //===============================
  // Inputs
  wire[R_DATA_WIDTH-1:0] gg_in_aij[0:GG_NUM-1];
  wire gg_in_valid[0:GG_NUM-1];

  //Outputs
  wire[R_DATA_WIDTH-1:0] gg_out_rij[0:GG_NUM-1];
  wire[D_WIDTH   -1:0] gg_out_d[0:GG_NUM-1];

  wire gg_out_rotates[0:GG_NUM-1];
  wire gg_out_valid[0:GG_NUM-1];

  //===============================
  //   R_GRs
  //===============================
  wire signed[R_DATA_WIDTH-1:0] gr_r_in_aij  [0:R_GR_NUM-1];
  wire signed[D_WIDTH-1:0] gr_r_in_d[0:R_GR_NUM-1];
  wire gr_r_in_valid[0:R_GR_NUM-1];
  wire gr_r_in_rotates[0:R_GR_NUM-1];

  wire signed[R_DATA_WIDTH-1:0] gr_r_out_rij[0:R_GR_NUM-1];
  wire[D_WIDTH-1:0] gr_r_out_d[0:R_GR_NUM-1];

  wire gr_r_out_propogate[0:R_GR_NUM-1];
  wire gr_r_out_valid[0:R_GR_NUM-1];
  wire gr_r_out_rotates[0:R_GR_NUM-1];

  wire signed[R_DATA_WIDTH-1:0] gr_r_x_out[0:R_GR_NUM-1];
  wire signed[R_DATA_WIDTH-1:0] gr_r_y_out[0:R_GR_NUM-1];

  //===============================
  //   Q_GRs
  //===============================

  wire signed[Q_DATA_WIDTH-1:0] gr_q_in_aij  [0:Q_GR_NUM-1];
  wire signed[D_WIDTH-1:0] gr_q_in_d[0:Q_GR_NUM-1];

  wire gr_q_in_valid[0:Q_GR_NUM-1];
  wire gr_q_in_propogate [0:Q_GR_NUM-1];
  wire gr_q_in_rotates[0:Q_GR_NUM-1];

  wire signed[Q_DATA_WIDTH-1:0] gr_q_out_rij[0:Q_GR_NUM-1];

  wire[D_WIDTH-1:0] gr_q_out_d[0:Q_GR_NUM-1];
  wire gr_q_out_propogate[0:Q_GR_NUM-1];
  wire gr_q_out_valid[0:Q_GR_NUM-1];
  wire gr_q_out_rotates[0:Q_GR_NUM-1];

  wire signed[Q_DATA_WIDTH-1:0] gr_q_x_out[0:Q_GR_NUM-1];
  wire signed[Q_DATA_WIDTH-1:0] gr_q_y_out[0:Q_GR_NUM-1];

  //===============================
  //   Flags
  //===============================
  wire rd_data_done_f    = cordic_cnt == 15 && state_RD_DATA;
  wire cordic_cal_done_f = cordic_cnt == 28 && state_CAL;
  wire output_done_f     = cordic_cnt == 15 && state_OUTPUT;

  //===============================
  //   MAIN CTR
  //===============================
  always @(posedge clk or negedge rst_n)
  begin
    if(~rst_n)
    begin
      current_state <= RD_DATA;
    end
    else
    begin
      current_state <= next_state;
    end
  end

  always @(*)
  begin
    case(current_state)
      IDLE:
        next_state = RD_DATA;
      RD_DATA:
        next_state = rd_data_done_f ? CAL : RD_DATA;
      CAL:
        next_state = cordic_cal_done_f ? OUTPUT : CAL;
      OUTPUT: // OUTPUTING THE VALUES
        next_state = output_done_f     ? IDLE   : OUTPUT;
      default:
        next_state = IDLE;
    endcase
  end
  //===============================
  //   INPUT SIGN EXTENSION
  //===============================
  wire signed[R_DATA_WIDTH-1:0] extended_in = $signed({{(2){in[INPUT_DATA_WIDTH-1]}},in,{(10){1'b0}}});

  //==============================================
  //   R INPUT 4x FIFOs & valid_delay_line_ff
  //==============================================
  generate
    for(i = 0 ; i < 4 ; i = i +1)
      for(j=0;j<4;j=j+1)
      begin
        always @(posedge clk or negedge rst_n)
        begin
          if(~rst_n)
          begin
            valid_delay_line_ff <= 0;
            aij_shift_bufs[i][j] <= 0;
          end
          else if(state_RD_DATA && in_valid)
          begin
            case(cordic_cnt/4)
              0:
              begin
                aij_shift_bufs[0][0] <= extended_in;

                if(i>=1)
                begin
                  aij_shift_bufs[i][0] <= aij_shift_bufs[i-1][0];
                end
              end
              1:
              begin
                aij_shift_bufs[0][1] <= extended_in;
                if(i>=1)
                begin
                  aij_shift_bufs[i][1] <= aij_shift_bufs[i-1][1];
                end
              end
              2:
              begin
                aij_shift_bufs[0][2] <= extended_in;
                if(i>=1)
                begin
                  aij_shift_bufs[i][2] <= aij_shift_bufs[i-1][2];
                end
              end
              3:
              begin
                aij_shift_bufs[0][3] <= extended_in;
                if(i>=1)
                begin
                  aij_shift_bufs[i][3] <= aij_shift_bufs[i-1][3];
                end
              end
              default:
                aij_shift_bufs[i][j] <= 0;
            endcase
          end
          else if(state_CAL)
          begin
            valid_delay_line_ff <= { valid_delay_line_ff[6:0],sends_valid_f};

            if(valid_delay_line_ff[j]==1)
            begin
              if(i>=1)
              begin
                aij_shift_bufs[i][j] <= aij_shift_bufs[i-1][j];
              end
              else
              begin
                aij_shift_bufs[i][j] <= 0;
              end
            end
          end
          else
          begin
            ;
          end
        end
      end
  endgenerate

  wire sends_valid_f = (cordic_cnt%4 == 0) && cordic_cnt<=12;
  //===============================
  //   Q INPUT 4x FIFOs
  //===============================
  generate
    for(j=0;j<4;j=j+1)
    begin
      always @(posedge clk or negedge rst_n)
      begin
        if(~rst_n)
        begin
          qij_bufs[0]<=4'b0001;
          qij_bufs[1]<=4'b0010;
          qij_bufs[2]<=4'b0100;
          qij_bufs[3]<=4'b1000;
        end
        else if(valid_delay_line_ff[j+4] == 1)
        begin
          qij_bufs[j] <= {qij_bufs[j][2:0],qij_bufs[j][3]};
        end
        else
        begin
          ;
        end
      end
    end
  endgenerate

  //===============================
  //   CORDIC CNT
  //===============================
  always @(posedge clk or negedge rst_n)
  begin
    if(~rst_n)
    begin
      cordic_cnt <= 0;
    end
    else if(cordic_cal_done_f || rd_data_done_f || output_done_f || state_IDLE)
    begin
      cordic_cnt <= 0;
    end
    else if(state_RD_DATA && in_valid || state_CAL || state_OUTPUT)
    begin
      cordic_cnt <= cordic_cnt + 1;
    end
    else
    begin
      cordic_cnt <= cordic_cnt;
    end
  end

  //==============================================================
  //   CORDIC MAIN
  //==============================================================
  //===============================
  //   CORDIC INPUTS
  //===============================
  // R parts
  assign gg_in_aij[0]   = $signed(aij_shift_bufs[3][0]);
  assign gr_r_in_aij[0] = $signed(aij_shift_bufs[3][1]);
  assign gr_r_in_aij[1] = $signed(aij_shift_bufs[3][2]);
  assign gr_r_in_aij[2] = $signed(aij_shift_bufs[3][3]);

  assign gg_in_valid[0]   = valid_delay_line_ff[0];
  assign gr_r_in_valid[0] = valid_delay_line_ff[1];
  assign gr_r_in_valid[1] = valid_delay_line_ff[2];
  assign gr_r_in_valid[2] = valid_delay_line_ff[3];

  //Q parts
  assign gr_q_in_valid[0] = valid_delay_line_ff[4];
  assign gr_q_in_valid[1] = valid_delay_line_ff[5];
  assign gr_q_in_valid[2] = valid_delay_line_ff[6];
  assign gr_q_in_valid[3] = valid_delay_line_ff[7];

  assign gr_q_in_aij[0] = $signed({1'b0,qij_bufs[0][3],{(10){1'b0}}});
  assign gr_q_in_aij[1] = $signed({1'b0,qij_bufs[1][3],{(10){1'b0}}});
  assign gr_q_in_aij[2] = $signed({1'b0,qij_bufs[2][3],{(10){1'b0}}});
  assign gr_q_in_aij[3] = $signed({1'b0,qij_bufs[3][3],{(10){1'b0}}});

  //===============================
  //   CORDIC MODULES
  //===============================
  generate
    for ( i= 0; i<GG_NUM; i=i+1)
    begin
      GG #(
           .D_WIDTH(D_WIDTH),
           .DATA_WIDTH(R_DATA_WIDTH)
         ) u_GG(
           .a_ij(gg_in_aij[i]),
           .valid_i(gg_in_valid[i]),
           .clk(clk),
           .rst_n(rst_n),
           .clr_i(state_IDLE),

           .valid_d_o(gg_out_valid[i]),
           .rotates_d_o(gg_out_rotates[i]),
           .rij_ff_o(gg_out_rij[i]),
           .d_i_d_o(gg_out_d[i])
         );

    end

    for ( i= 0; i<R_GR_NUM; i=i+1)
    begin
      GR #(
           .D_WIDTH(D_WIDTH),
           .DATA_WIDTH(R_DATA_WIDTH),
           .Q_GR(0),
           .R_GR(1)
         ) u_GR(
           .clk(clk),
           .rst_n(rst_n),
           .clr_i(state_IDLE),

           .a_ij(gr_r_in_aij[i]),
           .valid_i(gr_r_in_valid[i]),
           .d_i(gr_r_in_d[i]),
           .rotates_i(gr_r_in_rotates[i]),

           .rij_ff_o(gr_r_out_rij[i]),
           .rotates_d_o(gr_r_out_rotates[i]),
           .valid_d_o(gr_r_out_valid[i]),
           .x_ff(gr_r_x_out[i]),
           .y_ff(gr_r_y_out[i]),
           .d_i_d_o(gr_r_out_d[i])
         );
    end

    for ( i= 0; i<Q_GR_NUM; i=i+1)
    begin
      GR #(
           .D_WIDTH(D_WIDTH),
           .DATA_WIDTH(Q_DATA_WIDTH),
           .Q_GR(1),
           .R_GR(0)
         ) u_GR(
           .clk(clk),
           .rst_n(rst_n),

           .a_ij(gr_q_in_aij[i]),
           .valid_i(gr_q_in_valid[i]),
           .d_i(gr_q_in_d[i]),
           .rotates_i(gr_q_in_rotates[i]),
           .clr_i(state_IDLE),

           .rij_ff_o(gr_q_out_rij[i]),
           .rotates_d_o(gr_q_out_rotates[i]),
           .valid_d_o(gr_q_out_valid[i]),
           .x_ff(gr_q_x_out[i]),
           .y_ff(gr_q_y_out[i]),
           .d_i_d_o(gr_q_out_d[i])
         );
    end

  endgenerate

  //===============================
  //   CORDIC PORTS CONNECTIONS
  //===============================
  //gr0 -> gg1
  assign gg_in_valid[1] = gr_r_out_valid[0];
  assign gg_in_aij[1]   = gr_r_out_rij[0];

  //gr3 -> gg2
  assign gg_in_valid[2] = gr_r_out_valid[3];
  assign gg_in_aij[2]   = gr_r_out_rij[3];

  //gr1 -> gr3
  assign gr_r_in_valid[3] = gr_r_out_valid[1];
  assign gr_r_in_aij[3]   = gr_r_out_rij[1];

  //gr2 -> gr4
  assign gr_r_in_valid[4] = gr_r_out_valid[2];
  assign gr_r_in_aij[4]   = gr_r_out_rij[2];

  //gr4 -> gr5
  assign gr_r_in_valid[5] = gr_r_out_valid[4];
  assign gr_r_in_aij[5]   = gr_r_out_rij[4];

  generate
    //gg0,gr0,gr1,gr2
    for ( i= 0; i<3; i=i+1)
    begin
      if(i==0)
      begin
        assign gr_r_in_d[0] = gg_out_d[0];
        assign gr_r_in_rotates[0] = gg_out_rotates[0];
      end
      else
      begin
        assign gr_r_in_d[i] = gr_r_out_d[i-1];
        assign gr_r_in_rotates[i] = gr_r_out_rotates[i-1];
      end
    end
  endgenerate

  //gg1 -> gr3
  assign gr_r_in_d[3] = gg_out_d[1];
  assign gr_r_in_rotates[3] = gg_out_rotates[1];

  //gr3 -> gr4
  assign gr_r_in_d[4] = gr_r_out_d[3];
  assign gr_r_in_rotates[4] = gr_r_out_rotates[3];

  //gg2 -> gr5
  assign gr_r_in_d[5] = gg_out_d[2];
  assign gr_r_in_rotates[5] = gg_out_rotates[2];

  //r_gr2 -> q_gr0
  assign gr_q_in_d[0] = gr_r_out_d[2];
  assign gr_q_in_rotates[0] = gr_r_out_rotates[2];

  //r_gr4 -> q_gr4
  assign gr_q_in_d[4] = gr_r_out_d[4];
  assign gr_q_in_rotates[4] = gr_r_out_rotates[4];

  //r_gr5 -> q_gr8
  assign gr_q_in_d[8] = gr_r_out_d[5];
  assign gr_q_in_rotates[8] = gr_r_out_rotates[5];

  // Connections of q PEs.
  generate
    //q's gr0 -> gr1 -> gr2 -> gr3 ... rows
    for ( i= 1; i<4; i=i+1)
    begin
      for (j=0;j<3;j=j+1)
      begin
        assign gr_q_in_d[i+j*4] = gr_q_out_d[(i+j*4)-1];
        assign gr_q_in_rotates[i+j*4] = gr_q_out_rotates[(i+j*4)-1];
      end
    end

    // q's column gr0 -> gr4 -> gr8
    for ( i= 0; i<4; i=i+1)
    begin //3
      for (j=1;j<3;j=j+1)
      begin //1
        assign gr_q_in_valid[i+j*4]     = gr_q_out_valid[i+(j-1)*4];
        assign gr_q_in_aij[i+j*4]       = gr_q_out_rij[i+(j-1)*4];
      end
    end
  endgenerate

  //===============================
  //   OUTPUTS
  //===============================
  // Feeding value to output buffers
  always @(posedge clk or negedge rst_n)
  begin
    if(~rst_n)
    begin
      out_q <= 0;
      out_r <= 0;
      out_valid <= 0;
    end
    else if(output_done_f)
    begin
      out_q <= 0;
      out_r <= 0;
      out_valid <= 0;
    end
    else if(state_OUTPUT)
    begin
      out_valid <= 1;
      case(cordic_cnt)
        0:
        begin
          out_q <= gr_q_y_out[0];
          out_r <= gg_out_rij[0][`GGR2OUTPUT];
        end
        1:
        begin
          out_q <= gr_q_y_out[1];
          out_r <= gr_r_y_out[0][`GGR2OUTPUT];
        end
        2:
        begin
          out_q <= gr_q_y_out[2];
          out_r <= gr_r_y_out[1][`GGR2OUTPUT];
        end
        3:
        begin
          out_q <= gr_q_y_out[3];
          out_r <= gr_r_y_out[2][`GGR2OUTPUT];
        end
        4:
        begin
          out_q <= gr_q_y_out[4];
          out_r <= 'd0;
        end
        5:
        begin
          out_q <= gr_q_y_out[5];
          out_r <= gg_out_rij[1][`GGR2OUTPUT];
        end
        6:
        begin
          out_q <= gr_q_y_out[6];
          out_r <= gr_r_y_out[3][`GGR2OUTPUT];
        end
        7:
        begin
          out_q <= gr_q_y_out[7];
          out_r <= gr_r_y_out[4][`GGR2OUTPUT];
        end
        8:
        begin
          out_q <= gr_q_y_out[8];
          out_r <= 'd0;
        end
        9:
        begin
          out_q <= gr_q_y_out[9];
          out_r <= 'd0;
        end
        10:
        begin
          out_q <= gr_q_y_out[10];
          out_r <= gg_out_rij[2][`GGR2OUTPUT];
        end
        11:
        begin
          out_q <= gr_q_y_out[11];
          out_r <= gr_r_y_out[5][`GGR2OUTPUT];
        end
        12:
        begin
          out_q <= gr_q_out_rij[8];
          out_r <= 'd0;
        end
        13:
        begin
          out_q <= gr_q_out_rij[9];
          out_r <= 'd0;
        end
        14:
        begin
          out_q <= gr_q_out_rij[10];
          out_r <= 'd0;
        end
        15:
        begin
          out_q <= gr_q_out_rij[11];
          out_r <= gr_r_out_rij[5][`GGR2OUTPUT];
        end
        default:
        begin
          out_q <= 0;
          out_r <= 0;
        end
      endcase
    end
  end
endmodule
