filename = 'omega_tre_pi_delt_pa_fire_med_referanse_ti_grader.mat';
m = matfile(filename);
array = m.test;

time = array(1,:);
data = array(4,:);

plot(time, data, 'r');
title('Step response pitch');
xlabel('Time [t]');
ylabel('Pitch [°]');
grid on;
hold on;
syms x;
fplot(10*heaviside(x-5), [0,35]);
legend('\omega = 3\pi/4','Pitch reference');
hold off;