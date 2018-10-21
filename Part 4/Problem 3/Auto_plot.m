filename1 = 'FILENAME.mat';
m1 = matfile(filename1);
array = m1.ans;

%%Time
time = array(1,:);

%Estimated vals
pitch_est = array(2,:);
pitch_rate_est = array(3,:);
elevation_est = array(4,:);
elevation_rate_est = array(5,:);
travel_est = array(6,:);
travel_rate_est = array(7,:);

%Measured vals
pitch_mes = array(8,:);
pitch_rate_mes = array(9,:);
elevation_mes = array(10,:);
elevation_rate_mes = array(11,:);
travel_mes = array(12,:);
travel_rate_mes = array(13,:);
figure;

%%Pitch
subplot(3,2,1);
hold on;
xlim([0 10]);
ylim([-150 230]);
plot(time, pitch_mes, 'r');
plot(time, pitch_est, '--b');
legend('Measured pitch','Estimated pitch');
xlabel('Time t [s]');
ylabel('Pitch [°]');

%%Pitch rate
subplot(3,2,2);
hold on;
xlim([0 10]);
ylim([-300 300]);
plot(time, pitch_rate_mes, 'r');
plot(time, pitch_rate_est, 'b');
legend('Measured pitch rate','Estimated pitch rate');
xlabel('Time t [s]');
ylabel('Pitch rate [°/s]');

%%Elevation
subplot(3,2,3);
hold on;
xlim([0 10]);
plot(time, elevation_mes, 'r');
plot(time, elevation_est, '--b');
legend('Measured elevation','Estimated elevation');
xlabel('Time t [s]');
ylabel('Elevation [°]');

%%Elevation rate
subplot(3,2,4);
hold on;
xlim([0 10]);
plot(time, elevation_rate_mes, 'r');
plot(time, elevation_rate_est, 'b');
legend('Measured elevation rate','Estimated elevation rate');
xlabel('Time t [s]');
ylabel('Elevation rate [°/s]');

%%Travel
subplot(3,2,5);
hold on;
xlim([0 10]);
plot(time, travel_mes, 'r');
plot(time, travel_est, '--b');
legend('Measured travel','Estimated travel');
xlabel('Time t [s]');
ylabel('Travel [°]');

%%Travel rate
subplot(3,2,6);
hold on;
xlim([0 10]);
plot(time, travel_rate_mes, 'r');
plot(time, travel_rate_est, 'b');
legend('Measured travel rate','Estimated travel rate');
xlabel('Time t [s]');
ylabel('Travel rate [°/s]');