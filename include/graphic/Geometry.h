/*
 * Geometry.h
 *
 *  Created on: 2016年7月6日
 *      Author: lijing
 */

#ifndef POLA_GEOMETRY_H_
#define POLA_GEOMETRY_H_

#include "graphic/Vertex.h"
#include "graphic/math/Vector.h"
#include "utils/Vector.h"

namespace pola {

namespace utils {
POLA_BASIC_TYPES_TRAITS(graphic::vec3)
POLA_BASIC_TYPES_TRAITS(graphic::vec2)
POLA_BASIC_TYPES_TRAITS(graphic::FColor4)
}

namespace graphic {

#define FLAG_GEOMETRY_DEFAULT 0x0000
#define FLAG_GEOMETRY_NORMAL 0x0001
#define FLAG_GEOMETRY_UV 0x0002
#define FLAG_GEOMETRY_COLOR 0x0004

/*
 *
 */
class Geometry {
public:
	Geometry(size_t size = 0, int flag = FLAG_GEOMETRY_DEFAULT);
	virtual ~Geometry();

	void alloc(size_t size = 0, int flag = FLAG_GEOMETRY_DEFAULT);

	void addVerrtex(const Vertex3& v);
	void addVerrtex(const TextureVertex3& v);
	void addVerrtex(const NormalTextureVertex3& v);
	void addVerrtex(const NormalColorTextureVertex3& v);

	const pola::graphic::vec3* positions() const;
	pola::graphic::vec3* positions();
	size_t positionCount() const;
	void addPosition(const pola::graphic::vec3& pos);

	const pola::graphic::vec3* normals() const;
	pola::graphic::vec3* normals();
	size_t normalCount() const;
	void addNormal(const pola::graphic::vec3& nor);

	const pola::graphic::vec2* uvs() const;
	pola::graphic::vec2* uvs();
	size_t uvCount() const;
	void addUv(const pola::graphic::vec2& uv);

	const pola::graphic::FColor4* colors() const;
	pola::graphic::FColor4* colors();
	size_t colorCount() const;
	void addColor(const pola::graphic::FColor4& cor);

	const uint16_t* indices() const;
	uint16_t* indices();
	size_t indexCount() const;
	void addIndex(uint16_t index);

	/* Declare for Buffered Objects */
	virtual bool bufferd();

protected:
	pola::utils::Vector<pola::graphic::vec3> mPositions;
	pola::utils::Vector<pola::graphic::vec3> mNormals;
	pola::utils::Vector<pola::graphic::vec2> mUvs;
	pola::utils::Vector<pola::graphic::FColor4> mColors;

	pola::utils::Vector<uint16_t> mIndices;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GEOMETRY_H_ */
