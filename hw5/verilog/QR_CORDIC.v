module GR #(
    parameter D_WIDTH = 4,
    parameter DATA_WIDTH = 20
) (
    input clk,
    input rst_n,

    input signed[D_WIDTH-1:0] in_valid,
    input signed[DATA_WIDTH-1:0] in,

    output reg signed[DATA_WIDTH-1:0] out_r,
    output reg signed[DATA_WIDTH-1:0] out_q
);
//===============================
//   PARAMETERS & GENVARS
//===============================
parameter GG_NUM   = 3;
parameter R_GR_NUM = 6;
parameter Q_GR_NUM = 12;
genvar i,j,k;

//===============================
//   GGs
//===============================
// Inputs
wire gg_in_valid[0:GG_NUM-1];
wire[DATA_WIDTH-1:0] gg_in_aij[0:GG_NUM-1];
wire[DATA_WIDTH-1:0] gg_in_propogate[0:GG_NUM-1];

//Outputs
wire[DATA_WIDTH-1:0] gg_out_rij[0:GG_NUM-1];
wire[D_WIDTH   -1:0] gg_out_d[0:GG_NUM-1];
wire gg_out_rotates[0:GG_NUM-1];
wire gg_out_valid[0:GG_NUM-1];

//===============================
//   R_GRs
//===============================
wire gr_r_in_valid[0:R_GR_NUM-1];
wire gr_r_in_aij  [0:R_GR_NUM-1];
wire gr_r_in_propogate [0:R_GR_NUM-1];
wire[D_WIDTH-1:0] gr_r_in_d[0:R_GR_NUM-1];
wire gr_r_in_rotates[0:R_GR_NUM-1];

wire[DATA_WIDTH-1:0] gr_r_out_rij[0:R_GR_NUM-1];
wire[D_WIDTH-1:0] gr_r_out_d[0:R_GR_NUM-1];
wire gr_r_out_propogate[0:R_GR_NUM-1];
wire gr_r_out_valid[0:R_GR_NUM-1];
wire gr_r_out_rotates[0:R_GR_NUM-1];

//===============================
//   Q_GRs
//===============================

wire gr_q_in_valid[0:Q_GR_NUM-1];
wire gr_q_in_aij  [0:Q_GR_NUM-1];
wire gr_q_in_propogate [0:Q_GR_NUM-1];
wire[D_WIDTH-1:0] gr_q_in_d[0:Q_GR_NUM-1];
wire gr_q_in_rotates[0:Q_GR_NUM-1];

wire[DATA_WIDTH-1:0] gr_q_out_rij[0:Q_GR_NUM-1];
wire[D_WIDTH-1:0] gr_q_out_d[0:Q_GR_NUM-1];
wire gr_q_out_propogate[0:Q_GR_NUM-1];
wire gr_q_out_valid[0:Q_GR_NUM-1];
wire gr_q_out_rotates[0:Q_GR_NUM-1];


//===============================
//   Connection of ports
//===============================
generate

    for ( i= 0; i<GG_NUM; i=i+1) begin
    GG #(
       .D_WIDTH(D_WIDTH),
       .DATA_WIDTH(DATA_WIDTH)
     ) u_GG(
       .a_ij(gg_in_aij[i]),
       .valid_i(gg_in_valid[i]),
       .propogate_i(gg_in_propogate[i]),

       .clk(clk),
       .rst_n(rst_n),

       .valid_d_o(gg_out_valid[i]),
       .rotates_d_o(gg_out_rotates[i]),
       .rij_ff_o(gg_out_rij[i]),
       .d_i_d_o(gg_out_d[i])
     );
    end

    for ( i= 0; i<R_GR_NUM; i=i+1) begin
    GR #(
      .D_WIDTH(D_WIDTH),
      .DATA_WIDTH(DATA_WIDTH)
    ) u_GR(
      .clk(clk),
      .rst_n(rst_n),

      .a_ij(gr_r_in_aij[i]),
      .valid_i(gr_r_in_valid[i]),
      .d_i(gr_r_in_d[i]),
      .propogate_i(gr_r_in_propogate[i]),
      .rotates_i(gr_r_in_rotates[i]),

      .rotates_d_o(gr_r_out_rotates[i]),
      .d_i_d_o(gr_r_out_d[i]),
      .rij_ff_o(gr_r_out_rij[i])
    );
    end

    for ( i= 0; i<Q_GR_NUM; i=i+1) begin
    GR #(
      .D_WIDTH(D_WIDTH),
      .DATA_WIDTH(DATA_WIDTH)
    ) u_GR(
      .clk(clk),
      .rst_n(rst_n),

      .a_ij(gr_q_in_aij[i]),
      .valid_i(gr_q_in_valid[i]),
      .d_i(gr_q_in_d[i]),
      .propogate_i(gr_q_in_propogate[i]),
      .rotates_i(gr_q_in_rotates[i]),

      .rotates_d_o(gr_q_out_rotates[i]),
      .d_i_d_o(gr_q_out_d[i]),
      .rij_ff_o(gr_q_out_rij[i])
    );
    end

endgenerate

//===============================
//   PORTS CONNECTIONS
//===============================
//gr0 -> gg1
assign gg_in_valid[1] = gr_r_out_valid[0];
assign gg_in_aij[1]   = gr_r_out_rij[0];
assign gg_in_propogate[1] = gr_r_out_propogate[0];

//gr3 -> gg2
assign gg_in_valid[2] = gr_r_out_valid[3];
assign gg_in_aij[2]   = gr_r_out_rij[3];
assign gg_in_propogate[2] = gr_r_out_propogate[3];

//gr1 -> gr3
assign gr_r_in_valid[3] = gr_r_out_valid[1];
assign gr_r_in_aij[3]   = gr_r_out_rij[1];
assign gr_r_in_propogate[3] = gr_r_out_propogate[1];

//gr2 -> gr4
assign gr_r_in_valid[4] = gr_r_out_valid[2];
assign gr_r_in_aij[4]   = gr_r_out_rij[2];
assign gr_r_in_propogate[4] = gr_r_out_propogate[2];

//gr4 -> gr5
assign gr_r_in_valid[5] = gr_r_out_valid[4];
assign gr_r_in_aij[5]   = gr_r_out_rij[4];
assign gr_r_in_propogate[5] = gr_r_out_propogate[4];

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
assign gr_r_in_d[3] = gr_r_out_d[1];
assign gr_r_in_rotates[3] = gr_r_out_rotates[1];

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

//r_gr8 -> q_gr5
assign gr_q_in_d[5] = gr_r_out_d[8];
assign gr_q_in_rotates[5] = gr_r_out_rotates[8];

// Connections of q PEs.
generate
    //q's gr0 -> gr1 -> gr2 -> gr3 ... rows
    for ( i= 1; i<4; i=i+1)
    begin
        for (j=0;j<3;j=j+1)
        begin
            begin
                assign gr_q_in_d[i+j*4] = gr_q_out_d[(i+j*4)-1];
                assign gr_q_in_rotates[i+j*4] = gr_q_out_rotates[(i+j*4)-1];
            end
        end
    end
    // q's column gr0 -> gr4 -> gr8
    for ( i= 0; i<4; i=i+1)
    begin //3
        for (j=1;j<3;j=j+1)
        begin //1
            begin
                assign gr_q_in_valid[i+j*4]     = gr_q_in_valid[i+(j-1)*4]
                assign gr_q_in_aij[i+j*4]       = gr_q_in_aij[i+(j-1)*4];
                assign gr_q_in_propogate[i+j*4] = gr_q_in_propogate[i+(j-1)*4];
            end
        end
    end
endgenerate





endmodule