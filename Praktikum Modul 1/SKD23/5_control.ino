

int P,I,D,LastError;
int kp = 0;
int ki = 0;
int kd = 0;

int controlPID(int feedback, int setPoint){
  int Error =  setPoint - feedback;
  P = kp*Error;
  I = I + (Error*ki);
  D = kd*(Error-LastError);
  LastError = Error;
  return P+I+D;
}
