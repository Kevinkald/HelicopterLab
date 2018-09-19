filename1 = 'omega_pi.mat';
m1 = matfile(filename1);
array1 = m1.omega_pi;

filename2 = 'omega_pi_delt_pa_to.mat';
m2 = matfile(filename2);
array2 = m2.omega_pideltpato;

filename3 = 'omega_pi_delt_pa_tre.mat';
m3 = matfile(filename3);
array3 = m3.omega_pideltpatre;

filename4 = 'omega_tre_pi_delt_pa_fire.mat';
m4 = matfile(filename4);
array4 = m4.omega_trepideltpafire;

time1 = array1(1,:);
data1 = array1(4,:);

time2 = array2(1,:);
data2 = array2(4,:);

time3 = array3(1,:);
data3 = array3(4,:);

time4 = array4(1,:);
data4 = array4(4,:);

plot(time1, data1, 'r');
title('Step response of pitch with different values of \omega');
xlabel('Time [t]');
ylabel('Pitch [°]');
grid on;
hold on;
syms x;
fplot(25*heaviside(x-5), [0,46]);
plot(time2, data2, 'g');
plot(time3, data3, 'm');
plot(time4, data4, 'c');
legend('\omega = \pi','Reference pitch','\omega = \pi/2','\omega = \pi/3','\omega = 3\pi/4')
hold off;