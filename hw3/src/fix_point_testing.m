format long
a = 2.7182;
W_Length = 16;
F_Length = 15;
% a = fi(a,1,W_Length); %(value , signed, word_length)
disp(a);

wn = [-0.064538882629 0.040689417609 0.418092273222 ...
              -0.788485616406 ...
              0.418092273222 0.040689417609 -0.064538882629];

fix_wn = fi(wn,1,W_Length);

acc = 0 ;
accf = fi(acc,1,W_Length);
for i = 1:length(fix_wn)
    accf = accf + fix_wn(i);
    %accf(:) = accf + fix_wn(i); % This keeps the value
end
