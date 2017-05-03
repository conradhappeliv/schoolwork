%%% generating and plotting more complex function

function siggraph
clear all
clf
t=-10:.5:10;
y=exp(-t).*sin(10*pi*t).* ustep(t+1); % .* is used to mean element by element multiplication, while * is used for matrix multiplication

stem(t,y); % discrete plot of the function y, can use plot(t,y) to make continuous plot







%%% unit step function, 
% y=ustep(t) = 1 ; t>=0 
% y=ustep(t) = 0 ; t<0 
% t can be matrix or scalar


function y=ustep(t)
y=(t>=0) % (t>=0) returns 1 (true) if t>=0, elase returns a 0 (false)



%%%%%%% Can plot the unit step function as follows:
% t= -5:0.1:5     % generates numbers from -5 to 5 in increments of 0.1
% y=ustep(t)
% plot(t,y)






