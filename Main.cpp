#include <iostream>
#include <thread>
#include <Windows.h>
#include "RandomGeneratorDLL.hpp"
#include "Structs.hpp"
#include "PollTemperatures.hpp"
#include "SetTemperatures.hpp"
using namespace std;

int _cdecl main() {
/*
	cout << "\tHi!\nI'll need some details before I can do my work!\nFill in these fields so I know what I'm doing\n";
	for (int i = 0; i < 2; i++) {
		cout << "Enter your AC minimum supported temperature.\n\tIf you don't know it look it up in it's manual or search it on the internet\nAC minimum temp: ";
		cin >> AC[i].ACMinTemp;

		cout << "Enter your AC maximum supported temperature.\n\tIf you don't know it look it up in it's manual or search it on the internet\nAC maximum temp: ";
		cin >> AC[i].ACMaxTemp;

		cout << "Enter your AC power.\n\tIf you don't know it look it up in it's manual or search it on the internet\nAC power: ";
		cin >> AC[i].ACPower;
	}*/

///Test values
	AC[0].ACMinTemp = 16;
	AC[0].ACMaxTemp = 30;
	AC[0].ACPowerCool = 3.5;
	AC[0].ACPowerHeat = 4.5;
	AC[1].ACMinTemp = 20;
	AC[1].ACMaxTemp = 32;
	AC[1].ACPowerCool = 3.52;
	AC[1].ACPowerHeat = 5.12;
	El.CostPerWatt = 0.32;
	AmbTemps.PrefTemp = 22;
	AmbTemps.MinTemp = 18;
	AmbTemps.MaxTemp = 24;
	AmbTemps.Humidity = 80;
///Test values

	///Set global max and min temps
	if (AC[0].ACMaxTemp < AC[1].ACMaxTemp) S[0].GlobalMaxTemp = S[1].GlobalMaxTemp = S[2].GlobalMaxTemp = S[3].GlobalMaxTemp = AC[0].ACMaxTemp;
	else S[0].GlobalMaxTemp = S[1].GlobalMaxTemp = S[2].GlobalMaxTemp = S[3].GlobalMaxTemp = AC[1].ACMaxTemp;

	if (AC[0].ACMinTemp > AC[1].ACMinTemp) S[0].GlobalMinTemp = S[1].GlobalMinTemp = S[2].GlobalMinTemp = S[3].GlobalMinTemp = AC[1].ACMinTemp;
	else S[0].GlobalMinTemp = S[1].GlobalMinTemp = S[2].GlobalMinTemp = S[3].GlobalMinTemp = AC[0].ACMinTemp;

/*
	while (El.CostPerWatt < 0.0F) {
		cout << "Please set your cost per kilowatt: ";
		cin >> El.CostPerWatt;
		if (!cin) {
			cin.clear();
			cin.ignore(1000, '\n');
		}
		if (El.CostPerWatt < 0.0)cout << "Let's be honest, you don't get paid by electrical companies...\n";
		else if (El.CostPerWatt == 0.0F) {
			cout << "Do you generate your own electricity?[Y/N] ";
			char q1 = '\0';
			cin >> q1;
			if (q1 == 'Y' || q1 == 'y') El.OwnElectricity = true;
		}
	}
	while (AmbTemps.PrefTemp < S[0].GlobalMinTemp || AmbTemps.PrefTemp > S[0].GlobalMaxTemp) {
		cout << "Please set your preffered temperature: ";
		cin >> AmbTemps.PrefTemp;
		if (!cin) {
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	while (AmbTemps.MinTemp < S[0].GlobalMinTemp || AmbTemps.MinTemp > S[0].GlobalMaxTemp) {
		cout << "Please set minimum temperature to set: ";
		cin >> AmbTemps.MinTemp;
		if (!cin) {
			cin.ignore();
			cin.clear(1000, '\n');
		}
	}
	while (AmbTemps.MaxTemp < AmbTemps.MinTemp || AmbTemps.MaxTemp > S[0].GlobalMaxTemp) {
		cout << "Please set maximum temperature to set: ";
		cin >> AmbTemps.MaxTemp;
		if (!cin) {
			cin.ignore();
			cin.clear(1000, '\n');
		}
		if (AmbTemps.MaxTemp <= AmbTemps.MinTemp) cout << "Maximum can't be below minimum. It doesn't work like that...\n";
	}
	while (AmbTemps.Humidity < 0.0F || AmbTemps.Humidity > 100.0F) {
		cout << "Please set your preffered humidity: ";
		cin >> AmbTemps.Humidity;
		if (!cin) {
			cin.ignore();
			cin.clear(1000, '\n');
		}
		if (AmbTemps.Humidity <= 0) cout << "\tHumidity can't be less than zero. That doesn't make sense...\n";
		else if (AmbTemps.Humidity > 100) cout << "\tHumidity cant be more than 100%. That doesn't make sense...\n";
	}
*/
#ifdef _WIN32
	system("CLS");
#elif _UNIX
	system("clear");
#endif

	cout << "\n\n\tYou're set up!\n\tWe'll handle things for you from here! Just throw an eye each week to catch any problems\n";

	thread POLL_THREAD(PollTemps);
	thread SET_TEMPS(SetTemps);
	POLL_THREAD.join();
	SET_TEMPS.join();

	return EXIT_SUCCESS;
}