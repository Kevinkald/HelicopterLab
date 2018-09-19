filename = 'omega_pi_delt_pa_to.mat';
m = matfile(filename);
array = m.omega_pideltpato;

time = array(1,:);
data = array(4,:);


subplot(2,2,1);
plot(time, data, 'r');
title('Step response pitch');
xlabel('Time [t]');
ylabel('Pitch [°]');
grid on;
hold on;
syms x;
fplot(25*heaviside(x-5), [0,38]);
legend('Measured pitch','Pitch reference');
hold off;

