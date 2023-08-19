module cordic_vector(
    input clk,
    input rst_n,
    input valid,
    input signed[7:0] x,
    input signed[7:0] y,
    output signed[7:0] reg x_rot,
    output signed[7:0] reg y_rot
    output reg done,
);

integer jdx;


// cnt
reg processing_f;
reg cnt;

reg signed[7:0] x_result,y_result,x_in,y_in;
reg signed[7:0] x_temp;
reg signed[7:0] angle;

// Flip flops
reg signed [7:0] x_result_ff,y_result_ff;
reg signed [7:0] x_result_wr,y_result_wr;

always @(posedge clk or negedge rst_n) begin:CTR
    if(~rst_n)
    begin
        processing_f <= 0;
        cnt <= 0;
    end
    else if(valid)
    begin
        processing_f <= 1;
        cnt <= cnt+1;
    end
    else if(cnt == 1)
    begin
        processing_f <= 0;
        cnt <= 0;
    end
end


always @(*)
begin
    x_in = x;
    y_in = y;

    x_result_wr = 0;
    y_result_wr = 0;
    angle_wr    = 0;
    x_temp   = 0;

    for(jdx=0;jdx<6;jdx++)
        if(cnt==0 & (x_result_ff*y_result_ff) >= $signed(0))
        begin
            x_temp      = x_in        + y_in/2;
            y_result_wr = y_result_ff + x_in/2;
            x_result_wr = x_temp;
            angle_wr    = angle_ff + alpha[jdx];
        end
        else
        begin
            x_temp      = x_result_ff - y_result_ff/2;
            y_result_wr = y_result_ff + x_result_ff/2;
            x_result_wr = x_temp;
            angle_wr    = angle_ff - alpha[jdx];
        end
end

always @(posedge clk or negedge rst_n)
begin
    if(~rst_n)
    begin
        done <= 0;
        x_rot <= 0;
        y_rot <= 0;
    end
    else if(cnt==1)
    begin
        done <= 1;
        x_rot <= x_result_wr;
        y_rot <= y_result_wr;
    end

end






endmodule