module alu#(
    parameter width = 8
  ) (
    input [width-1:0] a,
    input [width-1:0] b,
    input [2:0] op,
    output reg[width-1:0] result
  );

  always @(*)
  begin
    //Mux
    case (op)
      3'd0: result = a+b;// Operations +
      3'd1: result = a-b;// Operations -
      3'd2: result = a & b;
      3'd3: result = a | b;
      3'd4: result = a ^ b;
      default: result = a+b; // Prevent latch generation
    endcase
  end


endmodule