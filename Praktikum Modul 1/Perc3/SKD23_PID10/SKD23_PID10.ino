void general_setup() {
  Serial.begin(115200);
}
//Import Library
#include <Adafruit_MCP4725.h>

//Define PIN
#define PinEn 11
#define PinIn1 10
#define PinIn2 9
#define PinTachometer A0
#define PinPotensiometer A1

//Karakteristik Kit 10
int minimumTerdeteksiPositif = 32;
int minimumTerdeteksiNegatif = -34;
int minimumPutarPositif = 21;
int minimumPutarNegatif = -28;
int maksimumPositif = 79;
int maksimumNegatif = 78;

//Sensor Variabel
float Poten1, Poten2, Poten3, Tacho1, Tacho2, Tacho3;
int samplingWindow = 10;
int MaxTachometer = 700;

//Actuator Variabel
float Motor = 0.0;
int Direction, LastDirection = 0;

//Compensation Variabel
int InputSerial = 0;
int InputCompensated;

//Control Variabel
int setPointKecepatan;

float gain = 1;
float kp = 0;
float ti = 0;
float td = 0;

float ki = kp/ti;
float kd = kp*td;

float P,I,D,Error; 
float sumError = 0;
float LastError = 0;

//Timing Variabel
long Time, StartTime, LastTimeSampling, LastTimeInput, DeltaTime;
long TimeSampling = 25;
int WaktuInput = 3000;
