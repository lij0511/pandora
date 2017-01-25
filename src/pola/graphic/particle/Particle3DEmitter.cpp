/*
 * ParticleEmitter.cpp
 *
 *  Created on: 2016年7月25日
 *      Author: lijing
 */

#include "pola/graphic/particle/Particle3DEmitter.h"

namespace pola {
namespace graphic {

Particle3DEmitter::Particle3DEmitter() : _particleSystem(nullptr), mEnable(true) {
}

Particle3DEmitter::~Particle3DEmitter() {
	_particleSystem = nullptr;
}

void Particle3DEmitter::updateEmitter(Particle3D* particle, float deltaTime) {
}

void Particle3DEmitter::setEnable(bool enable) {
	mEnable = enable;
}

bool Particle3DEmitter::isEnable() const {
	return mEnable;
}

} /* namespace graphic */
} /* namespace pola */
