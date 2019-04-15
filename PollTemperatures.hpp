#pragma once
void PollTemps(int i) {
	for (int j = 0; j < 5; j++) {
		S[j].Temperature = GenerateRandomTemp(i); //Get temperature from sensors here
		std::cout << "S[" << j << "] - temp polled: " << S[j].Temperature << '\n';

		S[j].Humidity = GenerateRandomHumidity(i); //Get humidity from sensors here
		std::cout << "S[" << j << "] - humidity polled: " << S[j].Humidity << '\n';
	}
}