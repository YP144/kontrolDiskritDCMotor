void general_setup() {
  Serial.begin(115200);
}

unsigned long Time, StartTime, LastTimeSampling, LastTimeInput;
unsigned int TimeSampling = 25, DeltaTime;
unsigned int WaktuInput = 3000;
int InputSerial = 0, InputCompensated;
float Motor = 0.0;
float Poten1, Poten2, Poten3, Tacho1, Tacho2, Tacho3;

int minimumTerdeteksiPositif = 32;
int minimumTerdeteksiNegatif = -34;

#define PinTachometer A0
#define PinPotensiometer A1

int samplingWindow = 10;

int MaxTachometer = 700;

#include <Adafruit_MCP4725.h>

#define PinEn 11
#define PinIn1 10
#define PinIn2 9

int Direction, LastDirection = 0;
