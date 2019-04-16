#include <Chrono.h>
#include <LightChrono.h>

#define ACMaxTemp   30
#define ACMinTemp   16
#define ACCoolPower 3.4
#define ACHeatPower 3.6
#define MaxTemp     40
#define MinTemp     20
#define PrefTemp    30
#define CostPerkWh  0.3

Chrono CTIMER;

float AvgTemp, kWh;
unsigned long Time = 0;
byte AmbTemp, Humidity, TSens[5], CurrentTemp, ACNewTemp;
byte Temps[10] = {20, 24, 20, 21, 21, 22, 23, 22, 21, 22};
bool ACMode, ACRunning;

void setup() {
  Serial.begin(1200);
  pinMode(12, OUTPUT);  //AC[0] -> LED ON
  pinMode(11, OUTPUT);  //AC[0] -> LED OFF
  //rtc.begin();
}

void PollTemps(){
  for (byte i=0;i<10;i++){
    TSens[0]=Temps[i];
    TSens[1]=Temps[i];
    TSens[2]=Temps[i];
    TSens[3]=Temps[i];
    TSens[4]=Temps[i];
  }
}

void loop() {
    PollTemps();

    CurrentTemp = ((TSens[0] + TSens[1] + TSens[4]) / 3) + ((TSens[0] + TSens[2] + TSens[4]) / 3) >> 1;

    AvgTemp = ((TSens[1] + TSens[3] + TSens[4]) / 3) + ((TSens[2] + TSens[3] + TSens[4]) / 3) >> 1;
    CurrentTemp += AvgTemp;

    CurrentTemp >> 1;

    Serial.print("\nAverage temp= ");
    Serial.println(AvgTemp);
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
    //delay(1000);
}
