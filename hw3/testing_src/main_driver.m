WL=16;
FL=15;

% Broadcasting data types.
T = filterDataType('scaled',WL,FL);

% Useful tools for fix_point conversion cast.
B = cast(pi, 'like', A);
sig_len = 8;
xn = rand(1, sig_len);
wn = [0.037828455507 -0.023849465020 0.110624404418 0.377402855613 ...
          0.852698679009 0.377402855613 0.110624404418 -0.023849465020 ...
          -0.037828455507];

wn_fix = cast(wn, 'like', T.x);
xn_fix = cast(xn, 'like', T.x);
xn_len = length(xn);

% Seperate data types
buildInstrumentedMex filterSystem -o filterSystem_mex ...
    -args {xn_fix, wn_fix, xn_len,T} -histogram


% Float Algorithm
yn_float = filterSystemfloat(xn,wn,xn_len);

% Fix point algorithm
yn_fix = filterSystem_mex(xn_fix, wn_fix, xn_len,T);

% Verify results
showInstrumentationResults filterSystem_mex ...
    -proposeFL -defaultDT numerictype(1,16)

disp("yn_fix type:");
disp(class(yn_fix));
yn_fix;

err_v = yn_float - yn_fix;
err = double(sum(err_v));

disp("Error difference in total:")
disp(err / length(err_v));

% Code generation
codegen filterSystem ...
    -args {xn_fix, wn_fix, xn_len,T} -config:lib -report
