%%% rect function
% rect(t) = 1;  if |t|<0.5
% rect(t) = 0;  if |t|>0.5

function rectplot
clear all
clf
t=-3:0.1:3 
y=rect(t)
stem(t,y)


function y=rect(t)
y=(sign(t+0.5)-sign(t-0.5) >0) % sign(x) returns 1 for positive elements and -1 for negative elements



%%% example usage
% t=-3:0.1:3 
% y=rect(t)
% stem(t,y)

