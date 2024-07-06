int controlPID(float feedback, float setPoint){
  Error =  setPoint - feedback;
  sumError = sumError + Error;
  
  P = kp*Error;
  I = ki*sumError;
  D = kd*(Error-LastError)/(TimeSampling);
  
  LastError = Error;
  return deadzoneCompensator(gain*(P+I+D));
}
