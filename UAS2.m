gain = 6.358312037;
tau = 1.069171209;
timeDelay = 0.352603373;
timeSampling = 0.2;

tfSistemAwal = tf([gain],[tau 1],'InputDelay',timeDelay)
% tfSistemAwal.TimeUnit = 'milliseconds';

figure()
step(tfSistemAwal)
stepinfo(tfSistemAwal)
figure()
step(feedback(tfSistemAwal,1))



