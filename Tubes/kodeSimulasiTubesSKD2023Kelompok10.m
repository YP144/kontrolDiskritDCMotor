% Variable
gain = 0.7633;
tau = 0.0745;
timeDelay = 0.07;
ts = 0.01;

% gain = 0.847;
% tau = 0.0685;
% timeDelay = 0.0346;
% ts = 0.01;

t = 0:0.01:0.5;

% Initial System Transfer Function Modeling
tfSistemAwal = tf(gain,[tau 1],"InputDelay",timeDelay);
tfAprox = pade(tfSistemAwal);
tfAproxDiskrit = c2d(tfAprox,ts,'tustin');

% Initial System State Space Modeling
[Aawal,Bawal,Cawal,Dawal] = tf2ss(tfAproxDiskrit.Numerator{1},tfAproxDiskrit.Denominator{1});
stateSpaceAwal = ss(Aawal,Bawal,Cawal,Dawal);

% Initial System Performance Test
figure(1);
step(tfSistemAwal)
stepinfo(tfSistemAwal)
grid on;
hold on

step(tfAprox)
grid on;
hold off



% Check Controllability
co = ctrb(stateSpaceAwal);
controllability = rank(co);

% Check Observability
obs = obsv(stateSpaceAwal);
observability = rank(obs);

% Integrate System
Aint = [Aawal zeros(2,1); -Cawal 0];
Bint = [Bawal;0];

% LQR Control Parameter
Q = [1 0 0 ; 0 1 0 ; 0 0 1];
R = 1;

% Do LQR Control
[K,S,e] = lqrd(Aint,Bint,Q,R,ts);

% Make New System with Control
Anew = Aint - Bint*K;
Bnew = [0;0;1];
Cnew = [Cawal 0];
ssFinal = ss(Anew,Bnew,Cnew,Dawal);

% Performance test of controlled system
figure(3);
step(ssFinal)
stepinfo(ssFinal)
grid on