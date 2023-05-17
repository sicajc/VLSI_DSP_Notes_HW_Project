function datatype = qrDataType(dt, x_partial, y_partial, x_output, y_output)

    switch dt
        case 'double'
            datatype.x_partial = double([]);
            datatype.y_partial = double([]);
            datatype.x_output = double([]);
            datatype.y_output = double([]);
        case 'single'
            datatype.x_partial = single([]);
            datatype.y_partial = single([]);
            datatype.x_output = single([]);
            datatype.y_output = single([]);
        case 'fixed'
            F = fimath('RoundingMethod', 'Floor');
            % F.ProductWordLength
            % F = fimath('OverflowAction', 'Wrap', 'RoundingMethod', 'Zero', 'ProductMode', 'KeepMSB');
            % F = fimath('OverflowAction', 'Wrap', 'RoundingMethod', 'Convergent', 'ProductMode', 'KeepMSB');


            datatype.x_partial = fi([], 1, x_partial.WL, x_partial.FL,F);
            datatype.y_partial = fi([], 1, y_partial.WL, y_partial.FL,F);
            datatype.x_output = fi([], 1, x_output.WL, x_output.FL,F);
            datatype.y_output = fi([], 1, y_output.WL, y_output.FL,F);
        case 'scaled'
            % This runs computation in double but store data in fix point, a debugging type
            % To check how far your range for your fix-point, want to get all the possible range.
            datatype.x_partial = fi([], 1, x_partial.WL, x_partial.FL, 'DataType', 'ScaledDouble');
            datatype.y_partial = fi([], 1, y_partial.WL, y_partial.FL, 'DataType', 'ScaledDouble');
            datatype.x_output = fi([], 1, x_output.WL, x_output.FL, 'DataType', 'ScaledDouble');
            datatype.y_output = fi([], 1, y_output.WL, y_output.FL, 'DataType', 'ScaledDouble');
    end

end
