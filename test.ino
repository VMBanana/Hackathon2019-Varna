#include <Chrono.h>
#include <LightChrono.h>

//Constant params for AC
#define ACMaxTemp   30
#define ACMinTemp   16
#define ACCoolPower 3.4
#define ACHeatPower 3.6

//Constant params for User
#define MaxTemp     22
#define MinTemp     18
#define PrefTemp    20

//Cost per killowatt in BGN
#define CostPerkWh  0.18

Chrono CTIMER; //Timer

float kWh, logR2, R2, T, c1 = 1.009249522e-03,\
		c2 = 2.378405444e-04, c3 = 2.019202697e-07;
unsigned long Time = 0;
int Vo;
byte AmbTemp, AvgTemp, TSens[5], ACNewTemp;
bool ACMode, ACRunning;

void setup() {
	Serial.begin(1200);
	pinMode(12, OUTPUT);  //AC -> LED ON (GREEN)
	pinMode(11, OUTPUT);  //AC -> LED OFF(RED  )
}

float Thermistor(){
//THIS THERMISTOR IS NOT ACCURATE!!!
//+-10 DEGREES CELSIUS DIFFERANCE!!!
	Vo = analogRead(A0);  //Thermistor -> A0

//Steinhart-Hart Equation
	R2 = 10000 * (1023.0 / (float)Vo - 1.0);
	logR2 = log(R2);
	T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));

	return T - 273.15;
}

void loop() {
	for (byte i=0;i<4;i++) TSens[i]=trunc(Thermistor());  //Gets thermistor values

//Setting AVERAGE and CURRENT temperatures
	AvgTemp = ((TSens[0] + TSens[1] + TSens[4]) / 3) + ((TSens[0] + TSens[2] + TSens[4]) / 3) >> 1;
	AvgTemp += ((TSens[1] + TSens[3] + TSens[4]) / 3) + ((TSens[2] + TSens[3] + TSens[4]) / 3) >> 1;
	AvgTemp = AvgTemp >> 1;
	Serial.print("\nAverage temp= ");
	Serial.println(AvgTemp);

	(AvgTemp > PrefTemp)? ACMode = false : ACMode = true;

	if (ACMode) {
//Heating
		if (AvgTemp < PrefTemp || AvgTemp < MinTemp) {
			CTIMER.restart();

			ACRunning = true;
			ACNewTemp = AvgTemp;

			Serial.println("AC is heating");

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

			Serial.println("AC is cooling");

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

	float T = Time / 1000;

	Serial.println(T);

	T /= 3600;

	(ACMode)? kWh = (T * ACHeatPower) : kWh = (T * ACCoolPower);

	Serial.print("kWh = ");
	Serial.println(kWh);
}