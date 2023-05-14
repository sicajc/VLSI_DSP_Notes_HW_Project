`define CYCLE_TIME 10
module GG_GR_tb;

  parameter DATA_WIDTH = 20;
  parameter D_WIDTH = 4;

  reg rst_n,clk;
  reg[DATA_WIDTH-1:0] a_ij,aij_r;

  wire [DATA_WIDTH-1:0] rij_ff_o,rij_ffr_o;
  wire [D_WIDTH-1:0] d_i;

  initial clk = 0;
  always  #(`CYCLE_TIME/2.0)  clk = ~clk ;


  initial
  begin
    // 00000010010000000000  // GG x = 9.000000
    // 00000010010000000000  //    y = 9.000000
    // 00000011001011011001  //    r = 12.711914
    // (20,10) fix-point.
    rst_n = 1;
    a_ij  = 0; aij_r = 0;
    #(`CYCLE_TIME*5.0) rst_n = 0;
    #(`CYCLE_TIME*5.0) rst_n = 1;
    a_ij = 20'b00000010010000000000; // x = 9, y = 0

    #(`CYCLE_TIME*3.5);
    a_ij = 20'b00000010010000000000; // x = 9 , y = 8.988281
    // 0 1 0 0_0 0 0 1_1 1 1 1 // Expected di  00000101010000000000  // GG x = 21.000000

    aij_r = 20'b11111010110000000000; // x = -21 , y = 0
                                      // x_result -12.881836
                                      // y_result = 16.549805


    #(`CYCLE_TIME*50.0) $finish;
  end

  GG #(
       .D_WIDTH(D_WIDTH),
       .DATA_WIDTH(DATA_WIDTH)
     ) u_GG(
       .a_ij(a_ij),
       .clk(clk),
       .rst_n(rst_n),
       .rij_ff_o(rij_ff_o),
       .d_i(d_i)
     );


    GR #(
      .D_WIDTH(D_WIDTH),
      .DATA_WIDTH(DATA_WIDTH)
    ) u_GR(
      .a_ij(aij_r),
      .d_i(d_i),
      .clk(clk),
      .rst_n(rst_n),
      .rij_ff_o(rij_ffr_o)
    );


endmodule
