%%code snippets for understand the pid's actions based directly in
%%transfer functions and not yet in the microcontroller's form implementation 
% Author: Julio E. Marulanda
clear all
close all
%example transfer function of a plant 
%
%       G(s) =  ______1______
%                      S^2+10S+20
G = tf([1],[1 10 20]);
figure(1)
title('Step response form the plant')
step(G);

%PID transfer function
kp = 300; %300
ki  = 10;%10
kd = 0.8;%0.8
PID = tf([kd kp ki],[1 0]); 

%Feedback transfer function for the complete system (plant and PID action)
Gc = feedback(PID*G,1); 
figure(2)
title('Step response for controlled system')
step(Gc)
hold on

%%************************Discrete Control System************************** 
%in open and closed loop the greatest pole is: -5.385+17.049978i and the
%magnitude is P = 17.8802 so the sample time will be Ts <= 2pi/(10P) <= 0.03s -> Ts = 0.02
Ts = 0.005;
qo = kp+(ki*Ts)/2+kd/Ts;
q1 = (ki*Ts)/2-kp-(2*kd)/Ts;
q2 = -((ki*Ts)/2-kd/Ts);

% qo = kp+(ki)/2+kd; %no sample time in equations
% q1 = (ki)/2-kp-(2*kd);
% q2 = -((ki)/2-kd);

Gz     = c2d(G,Ts); %discrete model
PIDz  = tf([qo q1 q2],[1 -1 0],Ts); %discrete PID model
Gzc   = feedback(PIDz*Gz,1);
%figure(3)
title('Step response in discrete and continuous time')
step(Gzc);
legend('Continuous time control','Discrete time control')