/*
 * Geometry.h
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#ifndef POLA_GEOMETRY_H_
#define POLA_GEOMETRY_H_

#include "graphic/Vertex.h"
#include "utils/Vector.h"

namespace pola {
namespace graphic {

#define FLAG_GEOMETRY_DEFAULT 0x0000
#define FLAG_GEOMETRY_NORMAL 0x0001
#define FLAG_GEOMETRY_UV 0x0002
#define FLAG_GEOMETRY_COLOR 0x0004

class Geometry {
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
	size_t indexCount() const;
	void addIndex(uint16_t index);

protected:
	void setIndicesCapacity(size_t size);
protected:
	pola::utils::Vector<uint16_t> mIndices;

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
		mIndices.setCapacity(size);
	}
}

inline const uint16_t* Geometry::indices() const {
	return mIndices.array();
}
inline uint16_t* Geometry::indices() {
	return mIndices.editArray();
}
inline size_t Geometry::indexCount() const {
	return mIndices.size();
}
inline void Geometry::addIndex(uint16_t index) {
	mIndices.push(index);
}

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GEOMETRY_H_ */
