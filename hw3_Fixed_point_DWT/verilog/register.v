module register#(
    parameter width = 10
  ) (
    input clk,
    input rst,
    input signed [width-1:0] register_wr,
    output reg signed [width:0]  register_ff
  );

  always@(posedge clk)
  begin
    if(rst)
    begin
      register_ff <= 0;
    end
    else
    begin
      register_ff <= register_wr;
    end
  end
endmodule
