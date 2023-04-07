module mult#(
    parameter width = 11
  ) (
    input signed[width-1:0] a,
    input signed[width-1:0] b,
    output signed[2*width-1:0]c
  );

  assign c = a*b;

endmodule
