%funcion discretizada con un periodo de muestreo de Ts = 0.005s
% ver: http://www.ib.cnea.gov.ar/~instyctl/Tutorial_Matlab_esp/PID.html
u = [ 0 0 1 ]; %u = u(k-2)   u(k-1)   u(k)   
y = [ 0 0 0 ]; %y = y(k-2)   y(k-1)    y(k)
e = [ 0 0 0 ];  %e = e(k-2)  e(k-1)   e(k)             %error
setpoint = 1;
% qo = 460.025;
% q1 = -619.9750;
% q2 =  160;
k = 3;
iter = 0;
der = 0;
Ts = 0.01;
g = zeros(1,270);
t = linspace(0,Ts*length(g),length(g));
for s = 1:length(g)
    %y(k) = (1.229e-5)*u(k-1)+(1.209e-5)*u(k-2)+1.951*y(k-1)-0.9512*y(k-2); %Ts=0.005 %y(k) = (1.229e-5)*u(k-1)+(1.209e-5)*u(k-2)+1.951*y(k-1)-0.9512*y(k-2);
    %y(k) = (0.0007014)*u(k-1)+(0.0006138)*u(k-2)+1.644*y(k-1)-0.6703*y(k-2); %Ts = 0.04
    y(k) = (4.837e-5)*u(k-1)+(4.678e-5)*u(k-2)+1.903*y(k-1)-0.9048*y(k-2); %Ts = 0.01
     e(k-1) = e(k);
     e(k) = setpoint - y(k); %error
     %u(k) =  u(k-1)+380.1*e(k)-459.9*e(k-1)+79.95*e(k-2);        %u(k) = u(k-1)+(q1+q2)*e(k-1)+qo*e(k); %pid compute
    %u(k) = u(k-1)+(q1+q2)*e(k-1)+qo*e(k); 
    iter = iter+( (e(k)+e(k-1))*Ts )/2;
    der = (e(k)-e(k-1))/Ts;
    %u(k) = kp*e(k)+ki*interr+kd*(e(k)-e(k-1))/Ts;
    u(k) = kp*e(k)+ki*iter+kd*der; 
    g(s) = y(k);
    y(k-2) = y(k-1);
    y(k-1) = y(k);
    u(k-2) = u(k-1);
    u(k-1) = u(k);
end
%figure(2)
plot(t,g,'r')
grid on