void setup() {
  general_setup();
  sensor_setup();
  actuator_setup();
  print_header();
  StartTime = millis();
  LastTimeSampling = StartTime;
  LastTimeInput = StartTime;
  jenis = "pid1"; 

  if (jenis == "pi1"){
//    kp = 3.23589;
//    ti = 9.58821;
    TimeSampling = 30;
    kp = 1.2;
    ti = 6.5;
    td = 0;
    ki = kp/ti;
    kd = 0; }
  else if (jenis == "pid1"){
//    kp = 4.31451;
//    ti = 58.1104;
//    td = 14.528;
    TimeSampling = 30;
    kp = 1;
    ti = 6.2;
    td = 25;
    ki = kp/ti;
    kd = kp*td;}
  else if (jenis == "pi2"){
//    kp = 3.23589;
//    ti = 9.58821;
    TimeSampling = 10;
    kp = 1.3;
    ti = 2.8;
    td = 0;
    ki = kp/ti;
    kd = 0; }
  else if (jenis == "pid2"){
//    kp = 4.31451;
//    ti = 58.1104;
//    td = 14.528;
    TimeSampling = 10;
    kp = 0.8;
    ti = 1.8;
    td = 18;
    ki = kp/ti;
    kd = kp*td;}
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Time = millis();
  InputSerial = serial(InputSerial);
//  setPointKecepatan = ((float)InputSerial/100)*maksimumPositif;
  
  
  
if (Time - LastTimeInput >= WaktuInput) {
    LastTimeInput = Time;
    
    if (turn == 1){
      InputSerial = InputSerial + 30;
      if (inputCount == 2){
        inputCount = 1;
        turn = 2;
      }
      inputCount += 1;
    }
    else if (turn == 2){
      InputSerial = InputSerial - 30;
      if (inputCount == 3){
        inputCount = 1;
        turn = 0;
      }
      inputCount += 1;
    }
    else if (turn == 0){
      InputSerial = 0;
    }
  }
  
  if (Time - LastTimeSampling >= TimeSampling) {
    DeltaTime = Time - LastTimeSampling;
    LastTimeSampling = Time;
    
//    InputCompensated = deadzoneCompensator(InputSerial);
    
    Tacho3 = smooth_velocity_percentage();
    float feedbackKec = (float)Tacho3/maksimumPositif*100;

//    float mv = (float) controlPID(Tacho3, setPointKecepatan);
    float mv = (float) controlPID(feedbackKec, (float)InputSerial);
    
    
    if ((mv >=0) && (mv <=100)){
      mv = mv;
    }
    else if (mv <0){
      mv = 0;
    }
    else if (mv >100){
      mv = 100;
    }
    Motor = run_motor(mv);
    Serial.print(t);
    Serial.print("\t");
    Serial.print(InputSerial);
    Serial.print("\t");
    Serial.print(feedbackKec);
    Serial.print("\t");
    Serial.println(mv);
    t=t+TimeSampling;
  }
}

void print_header() {
  Serial.println("Time\tInput\tKecepatan\tsignalKontrol");
}
