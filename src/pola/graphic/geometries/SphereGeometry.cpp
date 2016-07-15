/*
 * SphereGeometry.cpp
 *
 *  Created on: 2016年7月7日
 *      Author: lijing
 */

#include "pola/graphic/geometries/SphereGeometry.h"

namespace pola {
namespace graphic {

SphereGeometry::SphereGeometry(float radius, uint32_t widthSegments, uint32_t heightSegments, float phiStart, float phiLength, float thetaStart, float thetaLength) {
	float thetaEnd = thetaStart + thetaLength;

	uint32_t vertexCount = ((widthSegments + 1) * (heightSegments + 1));
	setCapacity(vertexCount, FLAG_GEOMETRY_DEFAULT | FLAG_GEOMETRY_NORMAL | FLAG_GEOMETRY_UV);

	for (uint32_t y = 0; y <= heightSegments; y ++) {
		float v = float(y) / heightSegments;
		for (uint32_t x = 0; x <= widthSegments; x ++) {
			float u = float(x) / widthSegments;
			float px = - radius * cosf(phiStart + u * phiLength ) * sinf(thetaStart + v * thetaLength);
			float py = radius * cosf( thetaStart + v * thetaLength );
			float pz = radius * sinf( phiStart + u * phiLength ) * sinf( thetaStart + v * thetaLength );
			addPosition({px, py, pz});
			vec3 normal(px, py, pz);
			normal.normalize();
			addNormal(normal);
			addUv({u, 1 - v});
		}
	}

	for (uint32_t y = 0; y < heightSegments; y ++) {
		for (uint32_t x = 0; x < widthSegments; x ++) {
			uint32_t v1 = y * (widthSegments + 1) + x + 1;
			uint32_t v2 = y * (widthSegments + 1) + x;
			uint32_t v3 = (y + 1) * (widthSegments + 1) + x;
			uint32_t v4 = (y + 1) * (widthSegments + 1) + x + 1;
			if ( y != 0 || thetaStart > 0 ) {
				addIndex(v1);
				addIndex(v2);
				addIndex(v4);
			}
			if ( y != heightSegments - 1 || thetaEnd < M_PI ) {
				addIndex(v2);
				addIndex(v3);
				addIndex(v4);
			}
		}
	}
	computeBoundingBox();
}

SphereGeometry::~SphereGeometry() {
}

} /* namespace graphic */
} /* namespace pola */
