#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
/**
 * @brief Defines a perspective-viewing frustum in terms of its near, far, left, right, bottom, and top
 * parameters.
*/
struct Frustum {
	float_t near;
	float_t far;
	float_t left;
	float_t right;
	float_t bottom;
	float_t top;

	static Frustum makeFrustum(float_t fovy, float_t near, float_t far, float_t aspectRatio) {
		float_t t = near * tan((fovy * M_PI / 180.0) / 2);
		float_t b = -t;
		float_t r = t * aspectRatio;
		float_t l = -r;
		return Frustum{ near, far, l, r, b, t };
	}
};