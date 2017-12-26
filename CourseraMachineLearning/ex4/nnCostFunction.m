function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%

% Convert y to binary labels
% Cannot find a way to do it without for loop...
ry = zeros(num_labels, m);
for i = 1:m
    ry(y(i), i) = 1;
end

% Forward prop
z1 = Theta1 * ([ones(m, 1), X])';
a1 = sigmoid(z1);

z2 = Theta2 * [ones(1, m); a1];
a2 = sigmoid(z2);

% Cost
J = sum(sum(-ry .* log(a2) - (1-ry) .* log(1 - a2))) / m;

% Regularize the cost
th1 = Theta1(:, 2:end) .^ 2;
th2 = Theta2(:, 2:end) .^ 2;
J = J + (sum(sum(th1)) + sum(sum(th2)))*lambda/2/m;

% Run BP
a1 = [ones(1, m); a1];

e3 = a2 - ry;
e2 = (Theta2' * e3);
e2 = e2(2:end, :); % Remove error 0
e2 = e2 .* sigmoidGradient(z1);

a0 = [ones(m, 1), X];
% Big delta
d1 = e2 * a0;
d2 = e3 * a1';

% d1 = [zeros(size(d1, 1), 1), d1];
% d2 = [zeros(size(d2, 1), 1), d2];

Theta1_grad = d1/m;
Theta2_grad = d2/m;

reg_th1 = Theta1(:, 2:end) * lambda / m;
reg_th2 = Theta2(:, 2:end) * lambda / m;

reg_th1 = [zeros(size(reg_th1, 1), 1), reg_th1];
reg_th2 = [zeros(size(reg_th2, 1), 1), reg_th2];

Theta1_grad = Theta1_grad + reg_th1;
Theta2_grad = Theta2_grad + reg_th2;

% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];

end
