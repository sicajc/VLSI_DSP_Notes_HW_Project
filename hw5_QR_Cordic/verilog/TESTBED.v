`timescale 1ns/10ps
`define RTL

module TESTBED;

  parameter INPUT_DATA_WIDTH = 8;
  parameter DATA_WIDTH = 12;
  parameter D_WIDTH = 4;
  parameter R_DATA_WIDTH = 20;
  parameter Q_DATA_WIDTH = 12;


  wire clk, rst_n, in_valid;
  wire [INPUT_DATA_WIDTH-1:0] in;
  wire out_valid;
  wire [DATA_WIDTH-1:0] out_q;
  wire [DATA_WIDTH-1:0] out_r;


  QR_CORDIC #( .D_WIDTH(D_WIDTH),
               .DATA_WIDTH(DATA_WIDTH),
               .INPUT_DATA_WIDTH(INPUT_DATA_WIDTH),
               .R_DATA_WIDTH(R_DATA_WIDTH),
               .Q_DATA_WIDTH(Q_DATA_WIDTH))
               u_CORDIC(
              .clk(clk),
              .rst_n(rst_n),
              .in_valid(in_valid),
              .in(in),
              .out_valid(out_valid),
              .out_q(out_q),
              .out_r(out_r)
            );

  PATTERN u_PATTERN(
            .clk(clk),
            .rst_n(rst_n),
            .in_valid(in_valid),
            .in(in),
            .out_valid(out_valid),
            .out_q(out_q),
            .out_r(out_r)
          );

endmodule
