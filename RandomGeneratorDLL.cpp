#include "RandomGeneratorDLL.hpp"
float GenerateRandomTemp(int it) {
	float a[] = { 30.0F,20.0F,25.0F,19.0F,20.0F,20.0F,20.0F,15.0F,15.0F,15.0F };
	return a[it];
}

float GenerateRandomHumidity(int it) {
	float a[] = { 80.0F,50.0F,100.0F,100.0F,32.0F,0.0F,90.0F,60.0F,70.0F,89.0F };
	return a[it];
}