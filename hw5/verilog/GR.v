module GR #(
    parameter D_WIDTH = 4,
    parameter DATA_WIDTH = 20
) (
    input signed[DATA_WIDTH-1:0] a_ij,
    input signed[D_WIDTH-1:0] d_i,
    input clk,
    input rst_n,
    output reg signed[DATA_WIDTH-1:0] rij_ff_o
);

parameter K = 20'b0000000000_1001101101;
// I:10, F:10
genvar idx;

reg signed[DATA_WIDTH-1:0] x_ff,y_ff;

wire signed[DATA_WIDTH-1:0] iters_x_in;
wire signed[DATA_WIDTH-1:0] iters_y_in;
wire signed[DATA_WIDTH*2-1:0] K_product_x;
wire signed[DATA_WIDTH*2-1:0] K_product_y;
wire signed[DATA_WIDTH-1:0] K_extracted;

reg signed[DATA_WIDTH-1:0] iters_x[0:3];
reg signed[DATA_WIDTH-1:0] iters_y[0:3];

reg[1:0] cnt;
wire iters_done_f  = cnt == 2;
wire gr_done_f     = cnt == 3;
wire iters_start_f = cnt == 0;

always @(posedge clk) begin
    if(!rst_n)
    begin
        x_ff <= 0;
        y_ff <= 0;
        rij_ff_o <= 0;
    end
    else if(gr_done_f)
    begin
      x_ff <= x_ff;
      y_ff <= $signed({K_product_x[39],K_product_x[28:10]});
      rij_ff_o <= $signed({K_product_x[39],K_product_x[28:10]});
    end
    else
    begin
        x_ff <= iters_x[3];
        y_ff <= iters_y[3];
        rij_ff_o <= rij_ff_o;
    end
end

assign K_product_x = $signed(x_ff) * $signed(K);
assign K_extracted = {K_product_x[39],K_product_x[28:10]};

always @(posedge clk or negedge rst_n)
  begin
    if(~rst_n)
    begin
      cnt <= 0;
    end
    else if(gr_done_f)
    begin
      cnt <= 0;
    end
    else
    begin
      cnt <= cnt + 1;
    end
  end

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
endgenerate



endmodule