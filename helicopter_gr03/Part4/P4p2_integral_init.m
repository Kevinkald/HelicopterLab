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

%%%%%%%%%%%%%%% Part 3

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
     0, 10];%vd
 
Q0 = diag([100, 30, 1000]);

K0 = lqr(A0, B0, Q0, R);

         %p  &p_r  &e_r gam zeta
Q = diag([200, 300, 400, 100, 500]);%edot  

 
A = [A0 ,  zeros(3,2);
    C0,  zeros(2,2)];

B = [B0         ;
     zeros(2,2)];
     
C = [C0, zeros(2,2)];  

K = lqr(A, B, Q, R);

P = inv(C0*inv(B0*K0-A0)*B0);

%%%%%%% Part 4

%%%%Problem 2

A_e =  [[0  1 0 0 0 0]
        [0  0 0 0 0 0]
        [0  0 0 1 0 0]
        [0  0 0 0 0 0]
        [0  0 0 0 0 1]
        [k3 0 0 0 0 0]];
    
B_e =  [[0  0]
        [0  k1]
        [0  0]
        [k2 0]
        [0  0]
        [0  0]];
    
C_e =  [[1 0 0 0 0 0]
        [0 0 1 0 0 0]
        [0 0 0 0 1 0]];

  
observer = obsv(A_e, C_e);
rank(observer)

poles = zeros(6,1);
omegac = 28;
for i = 0:2
    poles(i+1) = omegac * exp(1j*(i*pi/20+pi/2+3*pi/8));
end
for i = 4:6
    poles(i) = conj(poles(i-3));
end

%%% Ploting poles
plot(real(poles),imag(poles),'r*');
hold on;

%%%Ploting sector lines
x1 = [0 real(poles(4))]
y1 = [0 imag(poles(4))]
pl = line(x1,y1);

x2 = [0 real(poles(1))]
y2 = [0 imag(poles(1))]
p2 = line(x2,y2);



%%Plot circle
n = 256;
dPhi = 2*pi/n;
phi = (-pi:dPhi:pi-dPhi);
z = omegac*exp(1j*phi);
C = [ real(z) ; imag(z) ];
plot(z);

%plot axis
line([0 0], [-omegac-10 omegac+10],'color','k','linewidth',0.5) %y-axis
line([-omegac-10 omegac+10], [0 0],'color','k','linewidth',0.5) %x-axis 

legend(strcat('Eigenvalues of (A-LC) with \sigma =', num2str(omegac)));
xlabel('Re');
ylabel('Im');
grid on;
axis([-omegac-5,omegac+5,-omegac-5,omegac+5])



L = place(A_e',C_e',poles)';
    
A_est = A_e-L*C_e;
eig(A_est)




%%%%%%%%%% Problem 3

C_elambda = [[0 0 1 0 0 0]
             [0 0 0 0 1 0]];
         
C_pe = [[1 0 0 0 0 0]
        [0 0 1 0 0 0]];

observer_elambda = obsv(A_e,C_elambda); % Full rank

ovserver_pe = obsv(A_e,C_pe); % Ikke full rank



    
