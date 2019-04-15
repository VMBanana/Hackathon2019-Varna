#pragma once
#include "PollTemperatures.hpp"
/*
*	Sets the temperature
*	Here's where the magic happens
*/
void SetTemps() {
	int j = 0;
	while (true) {

#ifdef _WIN32
		system("CLS");
#elif _UNIX
		system("clear");
#endif
		PollTemps(j);
		if (j == 9) j = 0;
		else j++;
		cout << "\tSetting...\n";

		float* AvgTemp = new float;
		*AvgTemp = ((S[0].Temperature + S[1].Temperature + S[4].Temperature) / 3) + ((S[0].Temperature + S[2].Temperature + S[4].Temperature) / 3) / 2;
		AmbTemps.CurrentTemp = *AvgTemp;

		*AvgTemp = ((S[1].Temperature + S[3].Temperature + S[4].Temperature) / 3) + ((S[2].Temperature + S[3].Temperature + S[4].Temperature) / 3) / 2;
		AmbTemps.CurrentTemp += (*AvgTemp);

		AmbTemps.CurrentTemp /= 2;

		cout << "\nAverage temp = " << *AvgTemp << '\n';
		for (int i = 0; i < 2; i++) {
			if (AC[0].Mode) {
				//Heating
				if (*AvgTemp < AmbTemps.PrefTemp || *AvgTemp < AmbTemps.MinTemp) {
					AC[i].Running = true;
					AC[i].ACNewTemp = *AvgTemp;
					cout << "AC is actiated\n";
				}
				else if (*AvgTemp >= AmbTemps.PrefTemp) {
					AC[i].Running = false;
					cout << "AC is deactiated\n";
				}
			}
			else {
				//Cooling
				if (*AvgTemp > AmbTemps.PrefTemp || *AvgTemp > AmbTemps.MaxTemp) {
					AC[i].Running = true;
					AC[i].ACNewTemp = *AvgTemp;
					cout << "AC is actiated\n";
				}
				else if (*AvgTemp <= AmbTemps.PrefTemp) {
					AC[i].Running = false;
					cout << "AC is deactiated\n";
				}
			}
		}
		delete AvgTemp;
		this_thread::sleep_for(chrono::seconds(2));
	}
}