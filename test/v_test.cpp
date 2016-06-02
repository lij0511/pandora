/*
 * gltest1.cpp
 *
 *  Created on: 2015年12月10日
 *      Author: lijing
 */

#include "graphic/Vector.h"
#include "graphic/Matrix4.h"

using namespace pola;
using namespace pola::graphic;

int main(int argc, char *argv[]) {

//	for (int i = 1; i <= 360; i ++) {
		vec3 position = {0, 0, 5};
		vec3 target = {0, 0, 4};

		vec3 t1 = (target - position).getHorizontalAngle();
		printf("x=%f, y=%f, z=%f\n", t1.x, t1.y, t1.z);
		t1.y -= 90;
		mat4 m;
		m.setRotationDegrees(vec3(t1.x, t1.y, 0));

		target = {0, 0, 1};
		m.transformVector(target);
		vec3 v = target;

		printf("x=%f, y=%f, z=%f\n", v.x, v.y, v.z);

//	}

	return 1;
}


