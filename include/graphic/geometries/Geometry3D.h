/*
 * Geometry3D.h
 *
 *  Created on: 2016年7月6日
 *      Author: lijing
 */

#ifndef POLA_GEOMETRY3D_H_
#define POLA_GEOMETRY3D_H_

#include "graphic/Geometry.h"

namespace pola {
namespace graphic {

/*
 *
 */
class Geometry3D : public Geometry {
public:
	Geometry3D(size_t size = 0, int flag = FLAG_GEOMETRY_DEFAULT);
	virtual ~Geometry3D();

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

	/* Declare for Buffered Objects */
	virtual bool bufferd();

protected:
	void setCapacity(size_t size, int flag = FLAG_GEOMETRY_DEFAULT);

protected:
	pola::utils::Vector<pola::graphic::vec3> mPositions;
	pola::utils::Vector<pola::graphic::vec3> mNormals;
	pola::utils::Vector<pola::graphic::vec2> mUvs;
	pola::utils::Vector<pola::graphic::FColor4> mColors;

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GEOMETRY3D_H_ */
