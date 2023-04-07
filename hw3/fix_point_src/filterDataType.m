function datatype = filterDataType(dt,filter_coef,lv1_output,lv2_output,lv3_output)
    switch dt
    case 'double'
        datatype.filter_coef = double([]);
        datatype.lv1_output = double([]);
        datatype.lv2_output = double([]);
        datatype.lv3_output = double([]);
    case 'single'
        datatype.filter_coef = single([]);
        datatype.lv1_output = single([]);
        datatype.lv2_output = single([]);
        datatype.lv3_output = single([]);
    case 'fixed'
        datatype.filter_coef= fi([],1,filter_coef.WL,filter_coef.FL);
        datatype.lv1_output = fi([],1,lv1_output.WL,lv1_output.FL);
        datatype.lv2_output = fi([],1,lv2_output.WL,lv2_output.FL);
        datatype.lv3_output = fi([],1,lv3_output.WL,lv3_output.FL);
    case 'scaled'
        % This runs computation in double but store data in fix point, a debugging type
        % To check how far your range for your fix-point, want to get all the possible range.
        datatype.filter_coef    = fi([],1,filter_coef.WL,filter_coef.FL,'DataType','ScaledDouble');
        datatype.lv1_output     = fi([],1,lv1_output.WL,lv1_output.FL,'DataType','ScaledDouble');
        datatype.lv2_output     = fi([],1,lv2_output.WL,lv2_output.FL,'DataType','ScaledDouble');
        datatype.lv3_output     = fi([],1,lv3_output.WL,lv3_output.FL,'DataType','ScaledDouble');
    end
end
