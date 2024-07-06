clc, clear, warning off

% Identifikasi Sistem
s = tf("s");
Gain = 0.8123*16/100;
Gain_p = 1;
Tau = 84.9;
DeadTime = 29.1; % can't be zero

% Pcrit = 1.26;
% tcrit = (128-47.4);
Pcrit = 0.304;
tcrit = 313;

sys = tf(Gain,[Tau 1],"InputDelay",DeadTime);
sys1 = sys*1/s;
sys1.TimeUnit = 'milliseconds';
% figure(3);
% step(sys1)
% xlim([0 5000]);

sys1_cl = (feedback(sys1,1));
sys1_cl.TimeUnit = 'milliseconds';
% figure(1);
% step(sys1_cl)
% xlim([0 5000]);

% % nyari p crit
% kp = 0.304
% ki = 0;
% kd= 0;

% % P
kp = 0.5*Pcrit;
ti = 0;
ki = 0;
td = 0;
kd = 0;

% % PI
% kp = 0.45*Pcrit;
% ti = 0.833*tcrit;
% ki = kp/ti;
% td = 0;
% kd = kp*td;
% % % 
% % PID
% kp = 0.6*Pcrit;
% ki = kp/(0.5*tcrit);
% kd = kp*0.125*tcrit;
% 
% PID Overshoot Kecil
% kp = 0.33*Pcrit;
% ki = kp/(0.5*tcrit);
% kd = kp*0.33*tcrit;
% % 
% % PID Tanpa Overshoot
% kp = 0.2*Pcrit;
% ki = kp/(0.3*tcrit);
% kd = kp*0.5*tcrit;

% PID Tanpa Overshoot
% kp = 0.3*Pcrit;
% ki = 0.0002;
% kd = kp*0.5*tcrit;

%Fungsi Pengontrol
PID = kp+ki/s+kd*s;
PID.TimeUnit = 'milliseconds';
sys2 = (feedback(sys1*PID,1));
sys2.TimeUnit = 'milliseconds';
setpoint = 1;
hold off;
figure(2);
step(sys2);
xlim([0 1500]);
stepinfo(sys2)
hold off;