filename1 = 'Data/LQR_W_INTEGRATOR_FIRST_STEP.mat';
m1 = matfile(filename1);
array1 = m1.LQR_W_INTEGRATOR_FIRST;

time1 = array1(1,:);
data1 = array1(3,:);

plot(time1, data1, 'r');
title('Step response LQR integral effect');
xlabel('Time t [s]');
ylabel('Pitch [°]');
grid on;
hold on;
syms x;
axis([0,30,-3,23]);
fplot(20*heaviside(x-11), [0,30.4]);
legend('Pitch', 'Pitch reference')
% hold off;