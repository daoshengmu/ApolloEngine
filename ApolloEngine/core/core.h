
#pragma once

#include <math.h>
#include "core/Vector3.h"
#include "core/Vector4.h"
#include "core/Matrix4x4.h"
#include "core/Quaternion.h"

namespace Apollo
{
	typedef Vector3<float> Vector3f;
	typedef Vector4<float> Vector4f;
	typedef unsigned short uint16;
	typedef unsigned int   uint;
	typedef Matrix4x4<float> Matrix4x4f;
	typedef Quaternion<float> Quaternionf;

#define HALF_PI 1.57079632f
#define PI      3.14159265f
#define TWO_PI  6.28318530f
#define DEGREE_TO_RADIAN(x)  ( (x) / (180) ) * (PI)
#define RADIAN_TO_DEGREE(x)  ( (x) * (180) ) / (PI)

}