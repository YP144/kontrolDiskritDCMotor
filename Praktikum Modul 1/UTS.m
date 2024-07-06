clc;clear;
gs = tf(3.37717,[0.72166 1])

st = 0.3225;
os = 0;

figure();
step(feedback(gs,1));
disp('karakteristik sistem awal :');
stepinfo(feedback(gs,1))

arrkp = [];
arrtd = [];
err = [];

kp = 0.1;
td = 0.01;


for i = 1:40

    kp = 0.1*i;

    for j = 1:40

        td = 0.1*j;
        gc = tf([kp*td kp],[1]);
        system = gc*gs;
        
        arrkp = [arrkp, kp];
        arrtd = [arrtd, td];

        settlingTime = stepinfo(feedback(system,1)).SettlingTime(1); 
        overshoot = stepinfo(feedback(system,1)).Overshoot(1);
        
        err = [err, abs(settlingTime-st)+abs(overshoot-os)];

    end
end

[errmin, idx] = min(err);
disp('kp terplih :');  
kp = arrkp(idx)
disp('td terpilih :');
td = arrtd(idx)

disp('transfer function pengontrol :');
gc = tf([kp*td kp],[1])
figure();
step(feedback(gc*gs,1));
disp('karakteristik sistem akhir :');
stepinfo(feedback(gc*gs,1))