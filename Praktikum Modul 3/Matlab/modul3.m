pCrit = 0.304;
tCrit = 89.7402;

gain = 0.8123*1;
tau = 84.9/1;
timeDelay = 29.1/1;
timeSampling = 10/1;

tfPosisi = tf(gain*16/100,[tau 1],'InputDelay',timeDelay)*tf(1,[1 0]);
tfPosisi.TimeUnit = 'milliseconds';

figure()
step(tfPosisi)
figure()
tfPosisiAprox = pade(tfPosisi);
tfPosisiAprox.TimeUnit = 'milliseconds';
rlocus(tfPosisiAprox)

figure()
step(feedback(pCrit*tfPosisiAprox,1))

