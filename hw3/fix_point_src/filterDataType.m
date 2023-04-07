function datatype = filterDataType(dt,WL,FL)
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
        datatype.filter_coef= fi([],1,WL,FL);
        datatype.lv1_output = fi([],1,WL,FL);
        datatype.lv2_output = fi([],1,WL,FL);
        datatype.lv3_output = fi([],1,WL,FL);
    case 'scaled'
        % This runs computation in double but store data in fix point, a debugging type
        % To check how far your range for your fix-point, want to get all the possible range.
        datatype.filter_coef    = fi([],1,WL,FL,'DataType','ScaledDouble');
        datatype.lv1_output     = fi([],1,WL,FL,'DataType','ScaledDouble');
        datatype.lv2_output     = fi([],1,WL,FL,'DataType','ScaledDouble');
        datatype.lv3_output     = fi([],1,WL,FL,'DataType','ScaledDouble');
    end
end
