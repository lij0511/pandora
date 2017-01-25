/*
 * Particle3DRender.h
 *
 *  Created on: 2016年11月11日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_PARTICLE_PARTICLE3DRENDER_H_
#define POLA_GRAPHIC_PARTICLE_PARTICLE3DRENDER_H_

#include "pola/utils/RefBase.h"

namespace pola {
namespace graphic {

class Particle3DSystem;

class Particle3DRender : public pola::utils::RefBase {
	friend class Particle3DSystem;
public:
	Particle3DRender();
	virtual ~Particle3DRender();

protected:
	Particle3DSystem *_particleSystem;
};

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_GRAPHIC_PARTICLE_PARTICLE3DRENDER_H_ */
