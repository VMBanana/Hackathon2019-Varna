#include <iostream>
#include <thread>
#include <chrono>
#include "RandomGeneratorDLL.hpp"

using namespace std;

#include "Structs.hpp"
#include "PollTemperatures.hpp"
#include "SetTemperatures.hpp"
#include "GetkWh.hpp"
#include "CLI.hpp"

int _cdecl main() {
	//CLI();
///Test values
	AC[0].ACMinTemp = 16;
	AC[0].ACMaxTemp = 30;
	AC[0].ACPowerCool = 3.5;
	AC[0].ACPowerHeat = 4.5;
	AC[0].Mode = false;
	AC[0].Running = true;
	AC[1].ACMinTemp = 20;
	AC[1].ACMaxTemp = 32;
	AC[1].ACPowerCool = 3.52;
	AC[1].ACPowerHeat = 5.12;
	AC[1].Mode = false;
	AC[1].Running = true;
	El.CostPerWatt = 0.32;
	AmbTemps.PrefTemp = 30;
	AmbTemps.MinTemp = 18;
	AmbTemps.MaxTemp = 24;
	AmbTemps.Humidity = 80;
///Test values

	///Set global max and min temps
	if (AC[0].ACMaxTemp < AC[1].ACMaxTemp) S[0].GlobalMaxTemp = S[1].GlobalMaxTemp = S[2].GlobalMaxTemp = S[3].GlobalMaxTemp = AC[0].ACMaxTemp;
	else S[0].GlobalMaxTemp = S[1].GlobalMaxTemp = S[2].GlobalMaxTemp = S[3].GlobalMaxTemp = AC[1].ACMaxTemp;

	if (AC[0].ACMinTemp > AC[1].ACMinTemp) S[0].GlobalMinTemp = S[1].GlobalMinTemp = S[2].GlobalMinTemp = S[3].GlobalMinTemp = AC[1].ACMinTemp;
	else S[0].GlobalMinTemp = S[1].GlobalMinTemp = S[2].GlobalMinTemp = S[3].GlobalMinTemp = AC[0].ACMinTemp;

#ifdef _WIN32
	system("CLS");
#elif _UNIX
	system("clear");
#endif

	cout << "\n\n\tYou're set up!\n\tWe'll handle things for you from here! Just throw an eye each week to catch any problems\n";

	thread SET_TEMPS(SetTemps);
	thread GET_KWH(GetkWh);
	SET_TEMPS.join();
	GET_KWH.join();

	return EXIT_SUCCESS;
}