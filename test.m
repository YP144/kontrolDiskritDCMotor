ts2 = 0.1;
g2 = tf(1,[1 -1.5 0.5] , ts2)
figure();
rlocus(g2)
grid on;
hold on;
ks = 0.7;
wn = 5;

x = -ks*wn
y = wn*sqrt(1-ks^2)
s = x + i*y
zg = exp(s*ts2)

plot(zg,'rx')

p1 = 1;
p2 = 0.5;
theta1 = rad2deg(angle(zg-p1))
theta2 = rad2deg(angle(zg-p2))
remangle = theta1 + theta2 - 180

thetazc = 90
thetapc = thetazc - remangle
% 
% pc = 0.6602 - (0.2463/tan(deg2rad(thetapc)))
% zc = 0.6602 - (0.2463/tan(deg2rad(thetazc)))
% 
% gc = tf([1 -zc],[1 -pc],0.1)
% 
% hold off;
% figure();
% rlocus(gc*g2);
% hold on;
% plot(zg,'rx');
% 
% a1 = abs(zg-p1)
% a2 = abs(zg-p2)
% a3 = abs(zg-pc)
% 
% b = abs(zg-zc)
% kc = (a1*a2*a3)/b