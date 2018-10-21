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
Joystick_gain_x = 1;
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

%%%%%%%%%% Transer functions
s = tf('s');
omega0 = 5;
zeta = 0.9;
%kpp = (omega0^2)/k1;
%kpd = (2*zeta * omega0)/k1;
kpp = 5;
kpd = 2*kpp/(sqrt(k1*kpp));
k_pp =kpp;
k_pd = kpd;
pitchControler = (k1*k_pp)/(s^2+k1*k_pd*s+k1*k_pp);
