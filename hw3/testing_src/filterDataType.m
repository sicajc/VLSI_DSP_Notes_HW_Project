function datatype = filterDataType(dt,WL,FL)
    switch dt
    case 'double'
        datatype.x = double([]);
        datatype.y = double([]);
    case 'single'
        datatype.x = single([]);
        datatype.y = single([]);
    case 'fixed'
        datatype.x = fi([],1,WL,FL);
        datatype.y = fi([],1,WL,FL);
    case 'scaled'
        % This runs computation in double but store data in fix point, a debugging type
        % To check how far your range for your fix-point, want to get all the possible range.
        datatype.x = fi([],1,WL,FL,'DataType','ScaledDouble');
        datatype.y = fi([],1,WL,FL-1,'DataType','ScaledDouble');
    end


end
