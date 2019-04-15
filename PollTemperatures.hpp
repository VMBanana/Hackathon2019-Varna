#pragma once
#include <Windows.h>
void PollTemps() {
	while (true) {
		for (int i = 0; i < 4; i++) {
			S[i].Temperature = GenerateRandomTemp(); //Get temperature from sensors here
			std::cout << "S[" << i << "] - temp polled: " << S[i].Temperature << '\n';
			S[i].Humidity = GenerateRandomHumidity(); //Get humidity from sensors here
			std::cout << "S[" << i << "] - humidity polled: " << S[i].Humidity << '\n';
			Sleep(500);
		}
	}
}