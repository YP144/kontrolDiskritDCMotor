%%
clc, clear, warning off

% Identifikasi Sistem
s = tf("s");
gain =0.150408;
tau =78.29644;
tdlay = 5.710542; % can't be zero

% Rootlocus System
sys0 = tf(gain*exp(-tdlay*s)/(tau*s+1));
sys1 = sys0*1/s
figure(1)
rlocus(pade(sys1))
%% 
Pcrit = 0.977; 
 
sys2 = tf(gain,[tau 1],"InputDelay",tdlay)
sys3 = sys2*1/s
sys_cl = (sys3/(sys3+1))
step(sys_cl)

Tcrit = (803 - 662);


%% variable (unit) [additional information]
% 
% > simulation time
% t     : time (second or millisecond)
% tr    : time resolution (second or millisecond) [simulation
% time resolution]
% te    : time end (second or millisecond) [simulation duration]
% > flow variable
% v     : velocity (percent)
% vm    : velocity measured (percent)
% sp    : set poin (percent)
% u     : input (percent) [for open loop]
% mv    : manipulated variable (percent)
% imv   : implemented mv (percent)
% dmv   : delayed mv (percent)
% sistem parameter
% tdlay : time delay (second or millisecond) [FOPDT dead time]
% gain  : gain () [FOP gain]
% tau   : time constant (second or millisecond [FOP time constant]
% control parameter
% ts    : time sampling (second or millisecond)
% kp    : proporsional gain ()
% ti    : time integral (second or millisecond)
% td    : time derivative (second or millisecond)


%% nilai awal
tr = 1;
te = 1000;
v = 0;
x=0;
vm = 0;
imv = 0;
sp = 75;
u = sp;
ts = 7;

% Controller Design : Ziegler Nichols FOPDT
Type = 1; % 1:P, 2:PI, 3:PID, otherwise:Your Parameter Control
switch Type
    case 1
        % Proportional Controller
        kp = 0.5*Pcrit;
        ti = 0;
        td =0;
    case 2
        % Proportional–Integral Controller
        kp = 0.45*Pcrit;
        ti = Kp/(0.833*tcrit);
        td = 0;
    case 3
        % Proportional–Integral–Derivative Controller
        kp = 0.6*Pcrit;
        ti = Kp/(0.5*tcrit);
        td = Kp*0.125*tcrit;
    case 4
        %PID Overshoot Kecil
        kp = 0.33*Pcrit;
        ki = Kp/(0.5*tcrit);
        td = Kp*0.33*tcrit;
    otherwise
       %PID Overshoot Besar
        kp = 0.2*Pcrit;
        ti = Kp/(0.3*tcrit);
        td = Kp*0.5*tcrit;
end

sampling = true;
t_dis_ol = [];
iu_dis_ol = [];
vm_dis_ol = [];

t_con_ol = [];
du_con_ol = [];
v_con_ol = [];
x=0;

%% open loop
for t=0:tr:te
    
    if sampling
        iu = d2a(u);
        t_dis_ol(end+1) = t;
        iu_dis_ol(end+1) = iu;
        vm_dis_ol(end+1) = vm;
    end

    du = delay(iu,t,tr,tdlay);
    v = first_order_process(tr,v,du,gain,tau);
    x = integrate(ts,v,x);
    [vm,sampling] = a2d(t,ts,x);

    t_con_ol(end+1) = t;
    du_con_ol(end+1) = du;
    v_con_ol(end+1) = x;
end

clear delay a2d
x=0;
v = 0;
vm = 0;
sampling = true;
t_dis_cl = [];
mv_dis_cl = [];
imv_dis_cl = [];
vm_dis_cl = [];

t_con_cl = [];
dmv_con_cl = [];
v_con_cl = [];

%% closed loop
for t=0:tr:te
    if sampling
        mv = control(sp,vm,kp,ti,td,ts);
        imv = d2a(mv);
        t_dis_cl(end+1) = t;
        mv_dis_cl(end+1) = mv;
        imv_dis_cl(end+1) = imv;
        vm_dis_cl(end+1) = vm;
    end

    dmv = delay(imv,t,tr,tdlay);
    v = first_order_process(tr,v,dmv,gain,tau);
    x = integrate(ts,v,x);
    [vm,sampling] = a2d(t,ts,x);

    t_con_cl(end+1) = t;
    dmv_con_cl(end+1) = dmv;
    v_con_cl(end+1) = x;
end

%% Grafik
figure(2)
hold off
plot([t_con_ol(1) t_con_ol(end)],[u u],'r-.')
hold on
plot(t_con_ol,v_con_ol,'b--')
plot(t_con_cl,v_con_cl,'g--')
stairs(t_dis_ol,vm_dis_ol,'b-')
stairs(t_dis_cl,vm_dis_cl,'g-')
legend('set point/input','open loop','closed loop')

figure(3)
hold off
plot([t_con_ol(1) t_con_ol(end)],[sp sp],'r-.')
hold on
plot(t_con_cl,v_con_cl,'g--')
stairs(t_dis_cl,vm_dis_cl,'g-')
stairs(t_dis_cl,imv_dis_cl,'m-')
plot(t_con_cl,dmv_con_cl,'c--')
legend('set point','output','output measured','input','delayed input')

figure(4)
hold off
stairs(t_dis_cl(2:end),mv_dis_cl(2:end),'k-.')
hold on
stairs(t_dis_cl,imv_dis_cl,'m-')
plot(t_con_cl,dmv_con_cl,'c--')
legend('manipulated variable','implemented mv','delayed mv')