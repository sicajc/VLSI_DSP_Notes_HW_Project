function datatype = qrDataType(dt,lut_coef,x_output,y_output,theta_output)
    switch dt
    case 'double'
        datatype.lut_coef = double([]);
        datatype.x_output = double([]);
        datatype.y_output = double([]);
        datatype.theta_output = double([]);
    case 'single'
        datatype.lut_coef = single([]);
        datatype.x_output = single([]);
        datatype.y_output = single([]);
        datatype.theta_output = single([]);
    case 'fixed'
        datatype.lut_coef= fi([],1,lut_coef.WL,lut_coef.FL);
        datatype.x_output = fi([],1,x_output.WL,x_output.FL);
        datatype.y_output = fi([],1,y_output.WL,y_output.FL);
        datatype.theta_output = fi([],1,theta_output.WL,theta_output.FL);
    case 'scaled'
        % This runs computation in double but store data in fix point, a debugging type
        % To check how far your range for your fix-point, want to get all the possible range.
        datatype.lut_coef    = fi([],1,lut_coef.WL,lut_coef.FL,'DataType','ScaledDouble');
        datatype.x_output     = fi([],1,x_output.WL,x_output.FL,'DataType','ScaledDouble');
        datatype.y_output     = fi([],1,y_output.WL,y_output.FL,'DataType','ScaledDouble');
        datatype.theta_output     = fi([],1,theta_output.WL,theta_output.FL,'DataType','ScaledDouble');
    end
end
