#include <Chrono.h>
#include <LightChrono.h>

#define ACMaxTemp   30
#define ACMinTemp   16
#define ACCoolPower 3.4
#define ACHeatPower 3.6
#define MaxTemp     22
#define MinTemp     18
#define PrefTemp    20
#define CostPerkWh  0.18

Chrono CTIMER;

float AvgTemp, kWh;
unsigned long Time = 0;
byte AmbTemp, Humidity, TSens[5], CurrentTemp, ACNewTemp;
bool ACMode, ACRunning;


int Vo;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin(1200);
  pinMode(12, OUTPUT);  //AC[0] -> LED ON
  pinMode(11, OUTPUT);  //AC[0] -> LED OFF
}

void PollTemps(){
  for (byte i=0;i<4;i++){
    TSens[i]=trunc(Thermistor());
  }
}

float Thermistor(){
  Vo = analogRead(A0);
  R2 = 10000 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  return T - 273.15;
}

void loop() {
    PollTemps();
    CurrentTemp = ((TSens[0] + TSens[1] + TSens[4]) / 3) + ((TSens[0] + TSens[2] + TSens[4]) / 3) >> 1;

    AvgTemp = ((TSens[1] + TSens[3] + TSens[4]) / 3) + ((TSens[2] + TSens[3] + TSens[4]) / 3) >> 1;
    CurrentTemp += AvgTemp;

    CurrentTemp >> 1;

    Serial.print("\nAverage temp= ");
    Serial.println(AvgTemp);

    (CurrentTemp > PrefTemp)? ACMode = true : ACMode = false;
    
    for (byte i = 0; i < 2; i++) {
      if (ACMode) {
        //Heating
        if (AvgTemp < PrefTemp || AvgTemp < MinTemp) {
          CTIMER.restart();
          ACRunning = true;
          ACNewTemp = AvgTemp;
          Serial.println("AC is activated");
          digitalWrite(12, HIGH);
          digitalWrite(11, LOW);
          Time += CTIMER.elapsed();
        }
        else if (AvgTemp >= PrefTemp) {
          ACRunning = false;
          Serial.println("AC is deactivated");
          digitalWrite(12, LOW);
          digitalWrite(11, HIGH);
        }
      }
      
      else {
        //Cooling
        if (AvgTemp > PrefTemp || AvgTemp > MaxTemp) {
          CTIMER.restart();
          ACRunning = true;
          ACNewTemp = AvgTemp;
          Serial.println("AC is activated");
          digitalWrite(12, HIGH);
          digitalWrite(11, LOW);
          Time += CTIMER.elapsed();
        }
        else if (AvgTemp <= PrefTemp) {
          ACRunning = false;
          Serial.println("AC is deactivated");
          digitalWrite(12, LOW);
          digitalWrite(11, HIGH);
        }
      }
    }

    float T = Time / 1000;
    Serial.println(T);
    T /= 3600;
    (ACMode)? kWh = (T * ACHeatPower) : kWh = (T * ACCoolPower);
    Serial.print("kWh = ");
    Serial.println(kWh);
}
