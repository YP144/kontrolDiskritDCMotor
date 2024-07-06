int controlPID(float feedback, float setPoint){
  Error =  setPoint - feedback;
  if(Error > 50){
    Error -= 100;
  }
  else if (Error < -50){
    Error += 100;
  }
  else{
    Error = Error;
  }
  sumError = sumError + (float)(Error*(float)((float)TimeSampling/1));
  
  P = kp*Error;
    I = ki*sumError;
    D = kd*(Error-LastError)/(float)((float)TimeSampling/1);
  
    LastError = Error;

    float output = gain*(P+I+D);
    if (output>40.0) {
      output =  40.0;
    }
    else if (output<-40.0) {
      output = -40.0;
    }
    return deadzoneCompensator(output);
}


//int controlPID(float feedback, float setPoint){
//    
//  if ((setPoint > feedback)&&((setPoint - feedback) <= 50)){
//    Error =  setPoint - feedback;
//    sumError = sumError + (float)(Error*(float)((float)TimeSampling/1000));
//  
//    P = kp*Error;
//    I = ki*sumError;
//    D = kd*(Error-LastError)/(float)((float)TimeSampling/1000);
//  
//    LastError = Error;
//    return deadzoneCompensator(gain*(P+I+D));
//  }
//  else if ((setPoint > feedback)&&((100 - setPoint + feedback) <= 50)){    
//    Error =  setPoint - feedback - 100;
//    sumError = sumError + (float)(Error*(float)((float)TimeSampling/1000));
//  
//    P = kp*Error;
//    I = ki*sumError;
//    D = kd*(Error-LastError)/(float)((float)TimeSampling/1000);
//  
//    LastError = Error;
//    return deadzoneCompensator(gain*(P+I+D));
//  }
//  else if ((setPoint < feedback)&&((feedback - setPoint) <= 50)){    
//    Error =  setPoint - feedback;
//    sumError = sumError + (float)(Error*(float)((float)TimeSampling/1000));
//  
//    P = kp*Error;
//    I = ki*sumError;
//    D = kd*(Error-LastError)/(float)((float)TimeSampling/1000);
//  
//    LastError = Error;
//    return deadzoneCompensator(gain*(P+I+D));
//  }
//  else if ((setPoint < feedback)&&((100 + setPoint - feedback) <= 50)){    
//    Error =  100 + setPoint - feedback;
//    sumError = sumError + (float)(Error*(float)((float)TimeSampling/1000));
//  
//    P = kp*Error;
//    I = ki*sumError;
//    D = kd*(Error-LastError)/(float)((float)TimeSampling/1000);
//  
//    LastError = Error;
//    return deadzoneCompensator(gain*(P+I+D));
//  }
//}

//float pidControl(float sv, float pv) {
//  if (sv > pv){
//    if ((sv - pv)<= 50){
//      pid_error = sv - pv;
//      pid_p = pid_kp*pid_error;  
//      pid_sum += pid_error*TimeSampling;
//      pid_i = pid_ki*pid_sum;
//      pid_d = pid_kd*(pid_error - pid_lasterror)/(TimeSampling);
//    
//      pid_lasterror = pid_error;
//      return ((pid_p) + (pid_i) + (pid_d));
//    }
//    else if ((100 - (sv - pv)) <= 50){
//      pid_error = -(100 - (sv - pv));
//      pid_p = pid_kp*pid_error;  
//      pid_sum += pid_error*TimeSampling;
//      pid_i = pid_ki*pid_sum;
//      pid_d = pid_kd*(pid_error - pid_lasterror)/(TimeSampling);
//    
//      pid_lasterror = pid_error;
//      return ((pid_p) + (pid_i) + (pid_d));
//    }
//  }
//  else if (sv < pv){
//    if ((pv - sv)<= 50){
//      pid_error = sv - pv;
//      pid_p = pid_kp*pid_error;  
//      pid_sum += pid_error*TimeSampling;
//      pid_i = pid_ki*pid_sum;
//      pid_d = pid_kd*(pid_error - pid_lasterror)/(TimeSampling);
//    
//      pid_lasterror = pid_error;
//      return ((pid_p) + (pid_i) + (pid_d));
//    }
//    else if ((100 - (pv - sv)) <= 50){
//      pid_error = 100 - (pv - sv);
//      pid_p = pid_kp*pid_error;  
//      pid_sum += pid_error*TimeSampling;
//      pid_i = pid_ki*pid_sum;
//      pid_d = pid_kd*(pid_error - pid_lasterror)/(TimeSampling);
//    
//      pid_lasterror = pid_error;
//      return ((pid_p) + (pid_i) + (pid_d));
//    }
//  }
//}
