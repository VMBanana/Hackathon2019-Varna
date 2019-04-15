#pragma once

#ifdef RANDOMGENERATOR_EXPORTS
#define RANDOMGENERATOR __declspec(dllexport)
#else
#define RANDOMGENERATOR __declspec(dllimport)
#endif

extern "C" RANDOMGENERATOR float GenerateRandomTemp(int it);

extern "C" RANDOMGENERATOR float GenerateRandomHumidity(int it);