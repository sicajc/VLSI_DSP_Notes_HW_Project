`timescale 1ns/10ps

`include "PATTERN.v"
`ifdef RTL
  `include "QR_CORDIC.v"
`endif
`ifdef GATE
  `include "QR_CORDIC_SYN.v"
`endif

module TESTBED;

parameter DATA_WIDTH = 12;

wire clk, rst_n, in_valid;
wire [DATA_WIDTH-1:0] in;
wire out_valid;
wire [DATA_WIDTH-1:0] out_q;
wire [DATA_WIDTH-1:0] out_r;


initial begin
  `ifdef RTL
    $fsdbDumpfile("QR_CORDIC.fsdb");
  $fsdbDumpvars(0,"+mda");
  `endif
  `ifdef GATE
    $sdf_annotate("QR_CORDIC_SYN.sdf", u_SD);
    $fsdbDumpfile("QR_CORDIC_SYN.fsdb");
  $fsdbDumpvars(0,"+mda");
  `endif
end

QR_CORDIC u_SD(
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
    .out(out)
    .out_q(out_q),
    .out_r(out_r)
    );

endmodule