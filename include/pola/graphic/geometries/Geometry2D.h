/*
 * Geometry2D.h
 *
 *  Created on: 2016年7月14日
 *      Author: lijing
 */

#ifndef POLA_GEOMETRY2D_H_
#define POLA_GEOMETRY2D_H_

#include "pola/graphic/Geometry.h"

namespace pola {
namespace graphic {

class Geometry2D : public Geometry {
public:
	Geometry2D(size_t size = 0, int flag = FLAG_GEOMETRY_DEFAULT);
	virtual ~Geometry2D();

	void alloc(size_t size = 0, int flag = FLAG_GEOMETRY_DEFAULT);

	void addVerrtex(const Vertex2& v);
	void addVerrtex(const TextureVertex2& v);
	void addVerrtex(const ColorTextureVertex2& v);

	const pola::graphic::vec2* positions() const;
	pola::graphic::vec2* positions();
	size_t positionCount() const;
	void addPosition(const pola::graphic::vec2& pos);

	const pola::graphic::vec2* uvs() const;
	pola::graphic::vec2* uvs();
	size_t uvCount() const;
	void addUv(const pola::graphic::vec2& uv);

	const pola::graphic::FColor4* colors() const;
	pola::graphic::FColor4* colors();
	size_t colorCount() const;
	void addColor(const pola::graphic::FColor4& cor);

	virtual void computeBoundingBox();

protected:
	void setCapacity(size_t size, int flag = FLAG_GEOMETRY_DEFAULT);

protected:
	std::vector<pola::graphic::vec2> mPositions;
	std::vector<pola::graphic::vec2> mUvs;
	std::vector<pola::graphic::FColor4> mColors;

};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GEOMETRY2D_H_ */
