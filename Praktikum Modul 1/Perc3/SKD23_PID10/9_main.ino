void setup() {
  general_setup();
  sensor_setup();
  actuator_setup();
  print_header();
  StartTime = millis();
  LastTimeSampling = StartTime;
  LastTimeInput = StartTime;
  InputSerial = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Time = millis();
  
  if (Time - LastTimeInput >= WaktuInput) {

    LastTimeInput = Time;
    InputSerial = InputSerial + 5;
    
  }
  
  if (Time - LastTimeSampling >= TimeSampling) {
    DeltaTime = Time - LastTimeSampling;
    LastTimeSampling = Time;
    
    InputCompensated = deadzoneCompensator(InputSerial);
    
    Tacho3 = smooth_velocity_percentage();
    Poten3 = smooth_position_percentage();

    if(InputSerial < 0){
      setPointKecepatan = (InputSerial/100)*maksimumPositif;
    }
    else if (InputSerial > 0){
      setPointKecepatan = (InputSerial/100)*maksimumNegatif;
    }
    
    float mv = (float) controlPID(Tacho3, setPointKecepatan);
    Motor = run_motor(InputSerial);
    
    Serial.print(InputSerial);
    Serial.print("\t");
    Serial.print(Poten3);
    Serial.print("\t");
    Serial.println(Tacho3);
  }
}

void print_header() {
  Serial.println("Input\tPosisi\tKecepatan");
}
