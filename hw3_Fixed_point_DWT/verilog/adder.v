module adder#(
    parameter width = 10
  ) (
    input signed[width-1:0] a,
    input signed[width-1:0] b,
    output signed[width:0]c
  );

  assign c = a+b;

endmodule
