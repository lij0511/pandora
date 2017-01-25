/*
 * ParticleAffector.cpp
 *
 *  Created on: 2016年7月25日
 *      Author: lijing
 */

#include "pola/graphic/particle/Particle3DAffector.h"

namespace pola {
namespace graphic {

void Particle3DAffector::updateAffector(Particle3D* particle, float deltaTime) {
}

Particle3DAffector::Particle3DAffector()
: _particleSystem(nullptr)
, _isEnabled(true) {
}

Particle3DAffector::~Particle3DAffector() {
}

} /* namespace graphic */
} /* namespace pola */
