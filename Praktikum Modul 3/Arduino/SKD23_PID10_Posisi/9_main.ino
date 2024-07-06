int ganti = 0;
void setup() {
  general_setup();
  sensor_setup();
  actuator_setup();
  print_header();
  StartTime = millis();
  LastTimeSampling = StartTime;
  LastTimeInput = StartTime;
  jenis = "tunning"; 
  

  if (jenis == "p"){
    kp = 0.585;
    ti = 0;
    td = 0;
    ki = 0;
    kd = 0;  }

  else if (jenis == "pi"){

    kp = 0.5265;
    ti = 0;
    td = 0;
    ki = 0.004482644;
    kd = 14.528;}

  else if (jenis == "pid"){

    kp = 0.702;
    ti = 0;
    td = 0;
    ki = 0.009957447;
    kd = 12.37275;}

  else if (jenis == "pidkecil"){

    kp = 0.003319149;
    ti = 0;
    td = 0;
    ki = 0.003319149;
    kd = 10.998; }
    
  else if (jenis == "pidtanpa"){

    kp = 0.3861;
    ti = 0;
    td = 0;
    ki = 0.005476596;
    kd = 17.965233; }

  else if (jenis == "tunning"){

    kp = 0.45;
    ti = 0;
    td = 0;
    ki = 0;
    kd = 0.35; }
}


void loop() {
  // put your main code here, to run repeatedly:
  
  Time = millis();
  InputSerial = serial(InputSerial);
  
  if (Time - LastTimeInput >= WaktuInput) {

    LastTimeInput = Time;
//    if (InputSerial < 100){
//    InputSerial = InputSerial + 30;
//    }
//      if (ganti == 0){
//        
//        InputSerial = 50;
//        if (InputSerial == 50){
//          ganti = 1;
//      }
//      }
//    else if (ganti == 1){
//        
//        InputSerial = 20;
//        if (InputSerial == 20){
//          ganti = 2;
//        }
//      }
//      else if (ganti == 2){
//        
//        InputSerial = 50;
//        if (InputSerial == 50){
//          ganti = 3;
//        }
//      }
//      else if (ganti == 3){
//        
//        InputSerial = 90;
//        if (InputSerial == 90){
//          ganti = 4;
//        }
//      }
//      else if (ganti == 4){
//        
//        InputSerial = 20;
//        if (InputSerial == 20){
//          ganti = 5;
//        }
//      }
//      else if (ganti == 5){
//        
//        InputSerial = 0;
//
//      }
  }
  
  if (Time - LastTimeSampling >= TimeSampling) {
    DeltaTime = Time - LastTimeSampling;
    LastTimeSampling = Time;
    Poten3 = smooth_position_percentage();
    Tacho3 = smooth_velocity_percentage();
    
//    InputCompensated = deadzoneCompensator(InputSerial);

    float mv = (float) controlPID(Poten3, InputSerial);
//    if(mv > (40)){
//      mv = 40;
//    }
//    else if (mv < (-40)){
//      mv = -40;
//    }
    Motor = run_motor(mv);
    
//    Serial.print(Poten1);
//  Serial.print("\t");
//  Serial.print(Poten2);
//  Serial.print("\t");
    
    Serial.print(InputSerial);
    Serial.print("\t");
//    Serial.print(FeedbackPosisi);
    Serial.println(Poten3);
//    Serial.print("\t");
//    Serial.println(Tacho3);
//    Serial.print("\t");
//    Serial.println(mv);

//    feedbackPast = feedbackNow;
  }
}

void print_header() {
  Serial.println("Input\tPosisi");
}
