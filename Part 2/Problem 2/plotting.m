filename1 = 'travel_rate_negative_one_krp.mat';
m1 = matfile(filename1);
array1 = m1.travel_rate_data;

filename2 = 'travel_rate_negative_two_krp.mat';
m2 = matfile(filename2);
array2 = m2.travel_rate_data;
% 
% filename3 = 'omega_pi_delt_pa_tre.mat';
% m3 = matfile(filename3);
% array3 = m3.omega_pideltpatre;
% 
% filename4 = 'omega_tre_pi_delt_pa_fire.mat';
% m4 = matfile(filename4);
% array4 = m4.omega_trepideltpafire;

time = array1(1,:);
travel_rate_ref_1 = array1(2,:);
travel_rate_1 = array1(3,:);


time2 = array2(1,:);
travel_rate_ref_2 = array2(2,:);
travel_rate_2 = array2(3,:);

% 
% time3 = array3(1,:);
% data3 = array3(4,:);
% 
% time4 = array4(1,:);
% data4 = array4(4,:);

plot(time2, travel_rate_ref_2, 'g');
title('Step response of travel rate with different values of K_{rp}');
xlabel('Time t [s]');
ylabel('Travel rate [rad/s]');
hold on;
grid on;
plot(time, travel_rate_1, 'b');
plot(time2, travel_rate_2, 'm');
% plot(time2, data2, 'g');
% plot(time3, data3, 'm');
% plot(time4, data4, 'c');
legend('Reference travel rate','k_{rp}=-1', 'k_{rp}=-1.5');
hold off;