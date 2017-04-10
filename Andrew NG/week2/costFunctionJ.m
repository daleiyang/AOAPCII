function J = costFunctionJ(x,y,theta)
m = size(x,1);
predictions = x*theta;
sqrErrors = (predictions-y).^2;
J = 1/2*m * sum(sqrErrors);