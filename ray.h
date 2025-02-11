#pragma once

#include "vec.h"

// Point3 is a type alias for vec3 class

class ray {

private:
	point3 orig;
	vec3 dir;

public:
	
	ray() {}

	ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

	const point3& origin() const {
		return orig;
	}

	const vec3& direction() const {
		return dir;
	}

	// Computes the position of the ray at t
	point3 at(double t) {
		return orig + t * dir;
	}
};