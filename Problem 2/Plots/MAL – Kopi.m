filename1 = 'Data/LQR_WO_INTEGRATOR_FIRST.mat';
m1 = matfile(filename1);
array1 = m1.LRQ_WO_INTEGRATOR_FIRST;

filename2 = 'LRQ_WO_INTEGRATOR_SECOND.mat';
m2 = matfile(filename2);
array2 = m2.LRQ_WO_INTEGRATOR_SECOND;

time1 = array1(1,:);
data1 = array1(4,:);
data2 = array1(5,:);
data3 = array2(4,:);
data4 = array2(5,:);


plot(time1, data1, '--r');
title('Step response of pitch with different values of \omega');
xlabel('Time [t]');
ylabel('Pitch [°]');
grid on;
hold on;
syms x;
plot(time1, data2, 'g');
plot(time1, data3, '--b');
plot(time1, data4, 'o');
legend('Pitch reference1','Pitch1','Pitch reference','Pitch')
hold off;