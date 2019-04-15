#pragma once

#ifdef RANDOMGENERATOR_EXPORTS
#define RANDOMGENERATOR __declspec(dllexport)
#else
#define RANDOMGENERATOR __declspec(dllimport)
#endif

extern "C" RANDOMGENERATOR int GenerateRandomTemp(int seed);

extern "C" RANDOMGENERATOR int GenerateRandomHumidity(int seed);

extern "C" RANDOMGENERATOR int RandomGenerator(int seed);