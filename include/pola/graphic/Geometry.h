/*
 * Geometry.h
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#ifndef POLA_GEOMETRY_H_
#define POLA_GEOMETRY_H_

#include "pola/graphic/Vertex.h"
#include "pola/graphic/math/Math.h"
#include "pola/utils/TypeHelpers.h"
#include "pola/utils/RefBase.h"

#include <vector>

namespace pola {
namespace graphic {

#define FLAG_GEOMETRY_DEFAULT 0x0000
#define FLAG_GEOMETRY_NORMAL 0x0001
#define FLAG_GEOMETRY_UV 0x0002
#define FLAG_GEOMETRY_COLOR 0x0004

class Geometry : public pola::utils::RefBase {
public:
	enum Type {
		GEOMETRY_2D,
		GEOMETRY_3D,

		GEOMETRY_NONE,
	};

	Geometry(Type type = GEOMETRY_NONE);

	virtual ~Geometry() {};

	Type type() const;

	const uint16_t* indices() const;
	uint16_t* indices();
	virtual size_t indexCount() const;
	void addIndex(uint16_t index);

	void setBoundingBox(const Box3& boundingBox);
	const Box3& getBoundingBox() const;
	virtual void computeBoundingBox() = 0;

	virtual Geometry* clone() = 0;

protected:
	void setIndicesCapacity(size_t size);
protected:
	std::vector<uint16_t> mIndices;

	Box3 mBoundingBox;

private:
	Type mType;
};

inline Geometry::Geometry(Type type) : mType(type) {
}

inline Geometry::Type Geometry::type() const {
	return mType;
}

inline void Geometry::setIndicesCapacity(size_t size) {
	if (mIndices.capacity() != size) {
		mIndices.reserve(size);
	}
}

inline const uint16_t* Geometry::indices() const {
	return mIndices.data();
}
inline uint16_t* Geometry::indices() {
	return mIndices.data();
}
inline size_t Geometry::indexCount() const {
	return mIndices.size();
}
inline void Geometry::addIndex(uint16_t index) {
	mIndices.push_back(index);
}

inline void Geometry::setBoundingBox(const Box3& boundingBox) {
	mBoundingBox = boundingBox;
}
inline const Box3& Geometry::getBoundingBox() const {
	return mBoundingBox;
}

} /* namespace graphic */

namespace utils {
POLA_BASIC_TYPES_TRAITS(graphic::vec3)
POLA_BASIC_TYPES_TRAITS(graphic::vec2)
POLA_BASIC_TYPES_TRAITS(graphic::FColor4)
}

} /* namespace pola */

#endif /* POLA_GEOMETRY_H_ */
