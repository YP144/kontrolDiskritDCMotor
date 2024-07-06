ts = 0.2;
NIM = 26;

z = tf('z',ts);
tfSistemAwal = ( ( (2.1+NIM/10)*z )+(0.52*(1+NIM/10) ) ) / (z^2 - 0.57*z + 0.021*(1-NIM/10) ) 
gainP = 0.38;

% figure();
% step(gainP*tfSistemAwal)
% stepinfo(gainP*tfSistemAwal)
% 
% figure();
% step(feedback(gainP*tfSistemAwal,1))
% stepinfo(feedback(gainP*tfSistemAwal,1))
% 
% tfSistemAwalCont = d2c(tfSistemAwal);
% 
% figure();
% step(gainP*tfSistemAwalCont)
% stepinfo(gainP*tfSistemAwalCont)
% 
% figure();
% step(feedback(gainP*tfSistemAwalCont,1))
% stepinfo(feedback(gainP*tfSistemAwalCont,1))
% 
% figure();
% step(feedback(tfSistemAwalCont,1))
% stepinfo(feedback(tfSistemAwalCont,1))

g2 = gainP*tfSistemAwal
ts2 = 0.2;
figure();
rlocus(g2)

grid on;
hold on;
ks = 0.69010;
wn = 1.44906;

x = -ks*wn
y = wn*sqrt(1-ks^2)
s = x + i*y
zg = exp(s*ts2)

plot(zg,'rx')

% pole dan zero dari diagram root locus
p1 = 0.624;
p2 = -0.0539;
z1 = -0.398;

theta1 = rad2deg(angle(zg-p1))
theta2 = rad2deg(angle(zg-p2))
theta3 = rad2deg(angle(zg-z1))
remangle = theta1 + theta2 -theta3

thetapc = 144
thetazc = thetapc-remangle*2.8424

pc = 0.800789 - (0.170465/tan(deg2rad(thetapc)))
zc = 0.800789 - (0.170465/tan(deg2rad(thetazc)))

gc = tf([1 -zc],[1 -pc],ts2)

hold off;
figure();
rlocus(gc*g2);
hold on;
plot(zg,'rx');

a1 = abs(zg-p1)
a2 = abs(zg-p2)
a3 = abs(zg-pc)
a4 = abs(zg-z1)

b = abs(zg-zc)
kc = ((a1*a2*a3*a4)/b)
