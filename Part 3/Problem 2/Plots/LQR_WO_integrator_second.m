filename1 = 'Data/LQR_WO_integrator_SECOND.mat';
m1 = matfile(filename1);
array1 = m1.LQR_WO_integrator_SECOND;

time1 = array1(1,:);
pitch_ref = array1(2,:);
pitch = array1(3,:);
elevation_rate_ref = array1(4,:);
elevation_rate = array1(5,:);

plot(time1, pitch, 'r');
title('Controling pitch & elevation rate using the joystick');
xlabel('Time t [s]');
ylabel('Pitch [°] & Elevation rate [°/s]');
grid on;
hold on;
syms x;
axis([0,16,-25,20]);
plot(time1, pitch_ref, 'g--');
plot(time1, elevation_rate, 'c');
plot(time1, elevation_rate_ref, 'm--');
legend('Pitch', 'Pitch reference','Elevation rate', 'Elevation rate reference')
hold off;