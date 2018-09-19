filename = 'omega_pi.mat';
m = matfile(filename);
array = m.omega_pi;

time = array(1,:);
data = array(4,:);

plot(time, data, 'r');
title('Step response pitch');
xlabel('Time [t]');
ylabel('Pitch [°]');
grid on;
hold on;
syms x;
fplot(25*heaviside(x-5), [0,45.5]);
legend('Measured pitch','Pitch reference');
hold off;