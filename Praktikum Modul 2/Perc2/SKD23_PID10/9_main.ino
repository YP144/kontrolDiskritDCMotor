void setup() {
  general_setup();
  sensor_setup();
  actuator_setup();
  print_header();
  StartTime = millis();
  LastTimeSampling = StartTime;
  LastTimeInput = StartTime;
  jenis = "ccpid"; 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Time = millis();
//  InputSerial = serial(InputSerial);
//  setPointKecepatan = ((float)InputSerial/100)*maksimumPositif;
  
  if (jenis == "znp"){
    kp = 3.59543;
    ti = 0;
    td = 0;
    ki = 0;
    kd = 0;  }
  else if (jenis == "znpi"){
    kp = 3.23589;
    ti = 9.58821;
    td = 0;
    ki = kp/ti;
    kd = 0; }
  else if (jenis == "znpid"){
    kp = 4.31451;
    ti = 58.1104;
    td = 14.528;
    ki = kp/ti;
    kd = kp*td;}
  else if (jenis == "ccp"){
    kp = 4.00577;
    ti = 0;
    td = 0;
    ki = 0;
    kd = 0;}
  else if (jenis == "ccpi"){
    kp = 3.33847;
    ti = 56.8854;
    td = 0;
    ki = kp/ti;
    kd = 0;}
  else if (jenis == "ccpid"){
    kp = 5.10166;
    ti = 62.8661;
    td = 9.946;
    ki = kp/ti;
    kd = kp*td; }
  
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
