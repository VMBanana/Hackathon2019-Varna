#include <math.h>
#include <time.h>
#include <random>
#include "RandomGeneratorDLL.hpp"
#define RAND_MAX 50
int GenerateRandomTemp(int seed) {
	srand((unsigned int)time(NULL));
	int rnd = rand() % 10;
	seed *= rnd;
	return seed;
}

int GenerateRandomHumidity(int seed) {
	srand((unsigned int)time(NULL));
	int rnd = rand() % 10;
	if (rnd == 0)seed = 0;
	else seed /= rnd;
	return seed * 5;
}

int RandomGenerator(int seed) {
	srand(seed);
	return rand() % 10;
}