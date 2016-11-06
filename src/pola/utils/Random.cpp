/*
 * Random.cpp
 *
 *  Created on: 2016年11月3日
 *      Author: lijing
 */

#include "pola/utils/Random.h"

#include <time.h>
#include <stdlib.h>

namespace pola {

void seeding() {
	static bool seeded = false;
	if (!seeded) {
		seeded = true;
		srand(time(0));
	}
}

double random(double min, double max) {
	seeding();
	float r = rand_0_1();
	return min + (max - min) * r;
}
int random() {
	seeding();
	return rand();
}
float rand_minus1_1() {
	seeding();
	return ((rand() / (float)RAND_MAX) * 2) -1;
}
float rand_0_1() {
	seeding();
	return rand() / (float)RAND_MAX;
}

}
