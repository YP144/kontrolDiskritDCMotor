

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
  InputSerial = serial(InputSerial);
  
  Time = millis();
  
  if (Time - LastTimeInput >= WaktuInput) {

    LastTimeInput = Time;
//    InputSerial = InputSerial + 1;
    
  }
  
  if (Time - LastTimeSampling >= TimeSampling) {
    DeltaTime = Time - LastTimeSampling;
    LastTimeSampling = Time;
    InputCompensated = deadzoneCompensator(InputSerial);
    Motor = run_motor((float) InputSerial);
//    
//    Poten1 = sample_position_percentage();
//    Poten2 = smooth_position_percentage();
//    Tacho1 = sample_velocity_percentage();
//    Tacho2 = smooth_velocity_percentage();
//    
//    Poten1 = analogRead(PinPotensiometer);
//    Poten2 = sample_position_percentage();
//
//    Tacho1 = analogRead(PinTachometer);
//    Tacho2 = sample_velocity_percentage();
    Poten3 = smooth_position_percentage();
    Tacho3 = smooth_velocity_percentage();
    
//    Serial.print(DeltaTime);
//    Serial.print("\t");
//    Serial.print(Time - StartTime - TimeSampling);
//    Serial.print("\t");
    
    Serial.print(InputSerial);
    Serial.print("\t");
//    Serial.print(Motor);
//    Serial.print("\t");
    
//    Serial.print(Poten1);
//    Serial.print("\t");
//    Serial.print(Poten2);
//    Serial.print("\t");
    Serial.print(Poten3);
    Serial.print("\t");
//
//    Serial.print(Tacho1);
//    Serial.print("\t");
//    Serial.print(Tacho2);
//    Serial.print("\t");
    Serial.println(Tacho3);
  }
}

void print_header() {
  Serial.println("Input\tPosisi\tKecepatan");
}
