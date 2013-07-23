#pragma once


#define HALF_PI 1.57079632f
#define PI      3.14159265f
#define TWO_PI  6.28318530f
#define DEGREE_TO_RADIAN(x)  ( (x) / (180) ) * (PI)
#define RADIAN_TO_DEGREE(x)  ( (x) * (180) ) / (PI)

#define INVRANDMAX			(1.0f / (float)RAND_MAX)

namespace Apollo
{
	// return -1.0 ~ 1.0 random number
	static float FRAND()
	{
		return((float)rand() * INVRANDMAX * 2.0f - 1.0f);
	}
}