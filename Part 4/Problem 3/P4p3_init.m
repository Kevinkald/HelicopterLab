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

%%%%%%%%%% Transer functions
s = tf('s');
omega0 = 3*pi/4;
zeta = 1.0;
k_pp = (omega0^2)/k1;
k_pd = (2*zeta * omega0)/k1;
%k_pp =10;
%k_pd = 2*k_pp/(sqrt(k1*k_pp));
pitchControler = (k1*k_pp)/(s^2+k1*k_pd*s+k1*k_pp);

%%%%%%%%%%%%%%Problem 2

k_rp = -1;
offset_travel = -0.081;


%%%%%%%%%%%%%%%Task 3

%%%%%%%%%%%%%%% Problem 1

A0 = [0, 1, 0; 
     0, 0, 0; 
     0, 0, 0];

B0 = [0, 0; 
     0, k1; 
     k2, 0];
 
C0 = [1, 0 ,0;
      0, 0, 1];
 
R = [0.1, 0;%vs
     0, .5];%vd
 
Q0 = diag([100, 30, 1000]);

K0 = lqr(A0, B0, Q0, R);

         %p  &p_r  &e_r gam zeta
Q = diag([100, 100, 200, 50, 500]);%edot  

 
A = [A0 ,  zeros(3,2);
    C0,  zeros(2,2)];

B = [B0         ;
     zeros(2,2)];
     
C = [C0, zeros(2,2)];  

K = lqr(A, B, Q, R);

P = inv(C0*inv(B0*K0-A0)*B0);
%eig(A-B*K)

%%%%%%%PART 4

%%%%Problem 2

A_e =  [[0 1 0 0 0 0]
        [0 0 0 0 0 0]
        [0 0 0 1 0 0]
        [0 0 0 0 0 0]
        [0 0 0 0 0 1]
        [k3 0 0 0 0 0]];
    
B_e =  [[0 0]
        [0 k1]
        [0 0]
        [k2 0]
        [0 0]
        [0 0]];
    
C_e =  [[1 0 0 0 0 0]
        [0 0 1 0 0 0]
        [0 0 0 0 1 0]];

  
observer = obsv(A_e, C_e);
rank(observer)

%[b,a] = butter(6, 10);
% 
% eig(b)


poles = zeros(6,1);
omegac = 27; %18
for i = 0:2
    poles(i+1) = omegac * exp(1j*(i*pi/6+pi/2+pi/12));
end
for i = 4:6
    poles(i) = conj(poles(i-3))
end
poles
plot(real(poles),imag(poles),'*')
axis([-25,25,-25,25])
% polynom = poly(poles)
% zplane([0 0 0 0 0 0], pole(poles))

%pzmap(1/poly(poles))


L = place(A_e',C_e',poles)'

    
A_est = A_e-L*C_e;
eig(A_est)




%%%%%%%%%% Problem 3

C_elambda = [[0 0 1 0 0 0]
             [0 0 0 0 1 0]];
         
C_pe = [[1 0 0 0 0 0]
        [0 0 1 0 0 0]];

observer_elambda = obsv(A_e,C_elambda); % Full rank

ovserver_pe = obsv(A_e,C_pe); % Ikke full rank


omegac = 27; % 2 for elambda %18
for i = 0:2
    poles(i+1) = omegac * exp(1j*(i*pi/6+pi/2+pi/12));
end
for i = 4:6
    poles(i) = conj(poles(i-3))
end
poles


%L = place(A_e',C_elambda',poles)'
%A_est = A_e-L*C_elambda;

L = place(A_e',C_pe',poles)'
A_est = A_e-L*C_pe;
    
    
