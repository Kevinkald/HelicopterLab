% FOR HELICOPTER NR 3-10
% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert h�sten 2006 av Jostein Bakkeheim
% Oppdatert h�sten 2008 av Arnfinn Aas Eielsen
% Oppdatert h�sten 2009 av Jonathan Ronen
% Updated fall 2010, Dominik Breu
% Updated fall 2013, Mark Haring
% Updated spring 2015, Mark Haring


%%%%%%%%%%% Calibration of the encoder and the hardware for the specific
%%%%%%%%%%% helicopter
Joystick_gain_x = 0.8;
Joystick_gain_y = -1;


%%%%%%%%%%% Physical constants
g = 9.81; % gravitational constant [m/s^2]
l_c = 0.46; % distance elevation axis to counterweight [m]
l_h = 0.66; % distance elevation axis to helicopter head [m]
l_p = 0.175; % distance pitch axis to motor [m]
m_c = 1.92; % Counterweight mass [kg]
m_p = 0.72; % Motor mass [kg]

%%%%%%%%%%% Found values
k_f = 0.154;
v_s_star = 6.5;
j_p = 2*m_p*(l_p)^2;
j_e = m_c*(l_c)^2 + 2*m_p*(l_h)^2;
j_lambda = m_c*(l_c)^2 + 2*m_p*((l_h)^2 + (l_p)^2);
L_1 = l_p * k_f;
L_2 = g*(m_c*l_c-2*m_p*l_h);
L_3 = k_f*l_h;
L_4 = -k_f*l_h;
k1 = L_1/(j_p);
k2 = L_3/j_e;
k3 = -(L_4*L_2)/(j_lambda*L_3);


%%%%%%%%%%%%%%%Task 3

%%%%%%%%%%%%%%% Problem 2

A = [0, 1, 0; 
     0, 0, 0; 
     0, 0, 0];

B = [0, 0;
     0, k1; 
     k2, 0];
 
C = [1,0,0;
     0,0,1];%?
 
R = [0.1, 0;%vs
     0, 1];%vd


Q = [100, 0, 0;%p
     0, 30, 0;%pdot
     0, 0, 1000];%edot
 
  

K= lqr(A, B, Q, R);
P = inv(C*inv(B*K-A)*B);


eig(A-B*K)

