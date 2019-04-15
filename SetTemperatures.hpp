#pragma once
void SetTemps() {
	int i = 0;
	while (true) {

#ifdef _WIN32
		system("CLS");
#elif _UNIX
		system("clear");
#endif
		PollTemps(i);
		if (i == 9)i = 0;
		else i++;
		std::cout << "\tSetting...\n";

		float* AvgTemp = new float;
		*AvgTemp = ((S[0].Temperature + S[1].Temperature + S[4].Temperature) / 3) + ((S[0].Temperature + S[2].Temperature + S[4].Temperature) / 3) / 2;
		AmbTemps.CurrentTemp = *AvgTemp;

		*AvgTemp = ((S[1].Temperature + S[3].Temperature + S[4].Temperature) / 3) + ((S[2].Temperature + S[3].Temperature + S[4].Temperature) / 3) / 2;
		AmbTemps.CurrentTemp += (*AvgTemp);

		AmbTemps.CurrentTemp /= 2;

		std::cout << "\nAverage temp = " << *AvgTemp << '\n';

		if (AC[0].Mode) {
		//Heating
			if (*AvgTemp < AmbTemps.PrefTemp || *AvgTemp < AmbTemps.MinTemp) {
				AC[0].Running = true;
				AC[0].ACNewTemp = *AvgTemp;
				std::cout << "AC is actiated\n";
			}
			else if (*AvgTemp >= AmbTemps.PrefTemp) {
				AC[0].Running = false;
				std::cout << "AC is deactiated\n";
			}
		}
		else {
		//Cooling
			if (*AvgTemp > AmbTemps.PrefTemp || *AvgTemp > AmbTemps.MaxTemp) {
				AC[0].Running = true;
				AC[0].ACNewTemp = *AvgTemp;
				std::cout << "AC is actiated\n";
			}
			else if (*AvgTemp <= AmbTemps.PrefTemp) {
				AC[0].Running = false;
				std::cout << "AC is deactiated\n";
				;
			}
		}

		delete AvgTemp;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}