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

////Karakteristik Kit 10
//int minimumTerdeteksiPositif = 31;
//int minimumTerdeteksiNegatif = -32;
//int minimumPutarPositif = 25;
//int minimumPutarNegatif = -26;
//float maksimumPositif = 81;
//int maksimumNegatif = 82;

////Karakteristik Kit Hansen
//int minimumTerdeteksiPositif = 29;
//int minimumTerdeteksiNegatif = -30;
//int minimumPutarPositif = 22;
//int minimumPutarNegatif = -21;
//float maksimumPositif = 80;

//Karakteristik Kit dari kosan Farzak
int minimumTerdeteksiPositif = 29;
int minimumTerdeteksiNegatif = -34;
int minimumPutarPositif = 20;
int minimumPutarNegatif = -26;
float maksimumPositif = 80;

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
int jenis;
float setPointKecepatan;

float gain = 2*0.9259259;
float kp;
float ti;
float td;

float ki;
float kd;

float P,I,D,Error; 
float sumError = 0;
float LastError = 0;

float feedbackPosisi,feedbackNow,FeedbackPosisi,feedbackPast;

//Timing Variabel
long Time, StartTime, LastTimeSampling, LastTimeInput, DeltaTime;
long TimeSampling = 10;
int WaktuInput = 2000;
long timeImpulse;
