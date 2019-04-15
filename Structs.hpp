#pragma once
struct AC {
	float ACNewTemp = 0.0F;				//AC temperature to reach in Celsius
	float ACMinTemp = 0.0F;				//AC minimum temp in Celsius
	float ACMaxTemp = 0.0F;				//AC maximum temp in Celsius
	float ACPowerCool = 0.0F;			//AC power while cooling in kWh
	float ACPowerHeat = 0.0F;			//AC power while heating in kWh
	bool Mode = false;					//AC operating mode T = cooling F = heating
	bool Running = false;				//AC run flag T = active F = inactive
} AC[1];

struct Electricity {
	bool OwnElectricity = false;									//Electricity is generated (not being paid for)
	float CostPerWatt = -1.0F;										//Electricity cost in eur/kWh
	float TotalCost = 0.0F;											//Electricity total runtime cost
} El;

struct AmbientTemps {
	float CurrentTemp = 0.0F;			//Ambient temperature in Celsius /current/
	float CurrentHumidity = 0.0F;		//Ambient humidity in % /current/
	float MinTemp = 0.0F;				//Ambient minimum temperature in Celsius
	float MaxTemp = 0.0F;				//Ambient maximum temperature in Celsius
	float Humidity = 0.0F;				//Ambient humidity in %
	float PrefTemp = 0.0F;				//Ambient temperature in Celsius /preffered/
} AmbTemps;

struct Sensors {
	float GlobalMinTemp = 0.0F;			//Sensor minimum temperature /AC with highest MinTemp/
	float GlobalMaxTemp = 0.0F;			//Sensor maximum temperature /AC with lowest MaxTemp/
	float Temperature = 0;				//Sensor reported temperature in Celsius
	float Humidity = 0.0F;				//Sensor reported humidity in %
} S[5];