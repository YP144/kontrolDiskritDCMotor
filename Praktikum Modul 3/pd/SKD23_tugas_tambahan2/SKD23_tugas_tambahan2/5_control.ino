#define PID_SUM_MAX 10

// Parameter PID
float pid_kp = 0.8;
float pid_ki = 0;
float pid_kd = pid_kp*(0.01*1000);

float pid_error;
float pid_sum;
float pid_lasterror;

float pid_p;
float pid_i;
float pid_d;

void pidSetup() {
  pid_sum = 0;
  pid_error = 0;
  pid_lasterror = 0;
  pid_p = 0;
  pid_i = 0;
  pid_d = 0;
}

float pidControl(float sv, float pv) {
  if ((sv - pv)<= 50){
    pid_error = sv - pv;
    pid_p = pid_kp*pid_error;  
    pid_sum += pid_error*TimeSampling;
    pid_i = pid_ki*pid_sum;
    pid_d = pid_kd*(pid_error - pid_lasterror)/(TimeSampling);
  
    pid_lasterror = pid_error;
    return ((pid_p) + (pid_i) + (pid_d));
  }
  else if ((100 - sv + pv) <= 50){
    pid_error = pv - sv;
    pid_p = pid_kp*pid_error;  
    pid_sum += pid_error*TimeSampling;
    pid_i = pid_ki*pid_sum;
    pid_d = pid_kd*(pid_error - pid_lasterror)/(TimeSampling);
  
    pid_lasterror = pid_error;
    return ((pid_p) + (pid_i) + (pid_d));
  }
  //pid_error = sv - pv;
//  pid_p = pid_kp*pid_error;  
//  pid_sum += pid_error*TimeSampling;
//  pid_i = pid_ki*pid_sum;
//  pid_d = pid_kd*(pid_error - pid_lasterror)/(TimeSampling);
//
//  pid_lasterror = pid_error;
//  return (pid_p) + (pid_i) + (pid_d);
}
