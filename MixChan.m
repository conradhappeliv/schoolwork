function [x] = MixChan(x, t )
% MIXER
x = x .* cos(2*pi*3000*t);
% CHANNEL
for i=1:size(x),
   x(i) = x(i) +(-1 + (1+1)*rand(1));
end








