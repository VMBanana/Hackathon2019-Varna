#pragma once
/*
*	Temperature polling
*	Polls the temperature from temperature sensors
*	Right now it's linked with DLL simulating such sensors
*/
void PollTemps(int i) {
	for (int j = 0; j < 5; j++) {
		S[j].Temperature = GenerateRandomTemp(i); //Get temperature from sensors here
		cout << "S[" << j << "] - temp polled: " << S[j].Temperature << '\n';

		S[j].Humidity = GenerateRandomHumidity(i); //Get humidity from sensors here
		cout << "S[" << j << "] - humidity polled: " << S[j].Humidity << '\n';
	}
}