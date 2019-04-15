#pragma once
/*
*	Command Line Interface
*	Used for simple interfacing since this will be ran on Arduino or similar
*	microcontroller, so there won't be any space for graphical interfaces
*/
void CLI() {
	cout << "\tHi!\nI'll need some details before I can do my work!\nFill in these fields so I know what I'm doing\n";
	for (int i = 0; i < 2; i++) {
		cout << "Enter your AC minimum supported temperature.\n\tIf you don't know it look it up in it's manual or search it on the internet\nAC minimum temp: ";
		cin >> AC[i].ACMinTemp;

		cout << "Enter your AC maximum supported temperature.\n\tIf you don't know it look it up in it's manual or search it on the internet\nAC maximum temp: ";
		cin >> AC[i].ACMaxTemp;

		cout << "Enter your AC power when cooling.\n\tIf you don't know it look it up in it's manual or search it on the internet\nAC power: ";
		cin >> AC[i].ACPowerCool;

		cout << "Enter your AC power when heating.\n\tIf you don't know it look it up in it's manual or search it on the internet\nAC power: ";
		cin >> AC[i].ACPowerHeat;
	}
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
}