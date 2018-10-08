% FOR HELICOPTER NR 3-10
% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert høsten 2006 av Jostein Bakkeheim
% Oppdatert høsten 2008 av Arnfinn Aas Eielsen
% Oppdatert høsten 2009 av Jonathan Ronen
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
k1 = (l_p*k_f)/(j_p);
k2 = ((k_f*l_h)/(j_e));
k3 = (-k_f*l_h*g*(m_c*l_c - 2*m_p*l_h))/(j_lambda*k_f*l_h);
L1 = l_h*k_f;
L2 = k2*j_e;
L3 = l_h*k_f;
L4 = k_f*l_h*l_p;
offset_travel = -0.081;


%%%%%%%%%%%%%%%Task 3

%%%%%%%%%%%%%%% Problem 1

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


Q = [10, 0, 0;%p
     0, 3, 0;%pdot
     0, 0, 1000];%edot
 
K= lqr(A, B, Q, R);
D = 0;


%eig(A-B*K)


%%%%%Part 4%%%%%%%%%

%%%Problem 2%%%%%%%%%

A_e = [[0 1 0 0 0 0]
    [0 0 0 0 0 0]
    [0 0 0 1 0 0]
    [0 0 0 0 0 0]
    [0 0 0 0 0 1]
    [k3 0 0 0 0 0]];

B_e = [[0 0]
    [0 k1]
    [0 0]
    [k2 0]
    [0 0]
    [0 0]];

C_e = [[1 0 0 0 0 0]
    [0 0 1 0 0 0]
    [0 0 0 0 1 0]];

observer = obsv(A,C);
rank(observer)
%%Rank of the observer does match lenght of A--->Observable! :)

%THe following code adjusts the matrix gain L in a way that
%places the poles in a desired way.
L = place(A_e',C_e',[-3,-4,-5,-7,-8,-10]).'
eig(A_e-L*C_e)

%%Finding the LQR params with state estimation

R = [0.1, 0;%vs
     0, 1];%vd


Q = [10, 0, 0;%p
     0, 3, 0;%pdot
     0, 0, 1000]; %edot
 
K = lqr(A, B, Q, R)
P = inv(C*inv(B*K-A)*B);
D = 0;