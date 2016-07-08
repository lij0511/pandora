/*
 * CubeGeometry.cpp
 *
 *  Created on: 2016年7月8日
 *      Author: lijing
 */

#include "graphic/geometries/CubeGeometry.h"

namespace pola {
namespace graphic {

CubeGeometry::CubeGeometry(float w, float h, float d) {
	setCapacity(8, FLAG_GEOMETRY_DEFAULT | FLAG_GEOMETRY_NORMAL);
	addPosition({- w / 2, - h / 2, d / 2});
	addPosition({w / 2, - h / 2, d / 2});
	addPosition({w / 2, h / 2, d / 2});
	addPosition({- w / 2, h / 2, d / 2});
	addPosition({- w / 2, - h / 2, - d / 2});
	addPosition({w / 2, - h / 2, - d / 2});
	addPosition({w / 2, h / 2, - d / 2});
	addPosition({- w / 2, h / 2, - d / 2});

	vec3 normal = {- w / 2, - h / 2, d / 2};
	normal.normalize();
	addNormal(normal);
	normal = {w / 2, - h / 2, d / 2};
	normal.normalize();
	addNormal(normal);
	normal = {w / 2, h / 2, d / 2};
	normal.normalize();
	addNormal(normal);
	normal = {- w / 2, h / 2, d / 2};
	normal.normalize();
	addNormal(normal);
	normal = {- w / 2, - h / 2, - d / 2};
	normal.normalize();
	addNormal(normal);
	normal = {w / 2, - h / 2, - d / 2};
	normal.normalize();
	addNormal(normal);
	normal = {w / 2, h / 2, - d / 2};
	normal.normalize();
	addNormal(normal);
	normal = {- w / 2, h / 2, - d / 2};
	normal.normalize();
	addNormal(normal);

	addIndex(0);
	addIndex(1);
	addIndex(3);
	addIndex(1);
	addIndex(2);
	addIndex(3);

	addIndex(0);
	addIndex(3);
	addIndex(4);
	addIndex(3);
	addIndex(7);
	addIndex(4);

	addIndex(1);
	addIndex(5);
	addIndex(2);
	addIndex(5);
	addIndex(6);
	addIndex(2);

	addIndex(2);
	addIndex(7);
	addIndex(3);
	addIndex(2);
	addIndex(6);
	addIndex(7);

	addIndex(0);
	addIndex(4);
	addIndex(5);
	addIndex(0);
	addIndex(5);
	addIndex(1);

	addIndex(4);
	addIndex(7);
	addIndex(6);
	addIndex(4);
	addIndex(6);
	addIndex(5);
}

CubeGeometry::~CubeGeometry() {
}

} /* namespace graphic */
} /* namespace pola */
