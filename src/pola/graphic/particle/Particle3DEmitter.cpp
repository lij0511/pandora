/*
 * ParticleEmitter.cpp
 *
 *  Created on: 2016年7月25日
 *      Author: lijing
 */

#include "pola/graphic/particle/Particle3DEmitter.h"

namespace pola {
namespace graphic {

Particle3DEmitter::Particle3DEmitter() : mEnable(true) {
}

Particle3DEmitter::~Particle3DEmitter() {
}

void Particle3DEmitter::setEnable(bool enable) {
	mEnable = enable;
}

bool Particle3DEmitter::isEnable() const {
	return mEnable;
}

} /* namespace graphic */
} /* namespace pola */
