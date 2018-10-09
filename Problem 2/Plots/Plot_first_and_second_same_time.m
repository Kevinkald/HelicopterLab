filename1 = 'Data/LQR_WO_integrator_FIRST.mat';
m1 = matfile(filename1);
array1 = m1.LQR_WO_integrator_FIRST;

filename2 = 'Data/LQR_WO_integrator_SECOND.mat';
m2 = matfile(filename2);
array2 = m2.LQR_WO_integrator_SECOND;

time1 = array1(1,:);
data1 = array1(4,:);
data2 = array1(5,:);
time2 = array2(1,:);
data3 = array2(4,:);
data4 = array2(5,:);


plot(time1, data1, '--r');
title('Controling');
xlabel('Time [t]');
ylabel('Pitch [°]');
grid on;
hold on;
syms x;
axis([0,6,-5,20]);
plot(time1, data2, 'g');
plot(time2, data3, '--c');
plot(time2, data4, 'y');
legend('Pitch reference1','Pitch1','Pitch reference','Pitch')
hold off;