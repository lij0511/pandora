/*
 * Particle3DSystem.cpp
 *
 *  Created on: 2016年7月26日
 *      Author: lijing
 */

#include "pola/graphic/particle/Particle3DSystem.h"

#include "pola/log/Log.h"

namespace pola {
namespace graphic {

Particle3DSystem::Particle3DSystem()
	: _state(State::STOP)
	, _emitter(nullptr)
	, _render(nullptr)
	, _aliveParticlesCnt(0)
	, _particleQuota(0)
	, _blend({BlendFactor::FACTOR_SRC_ALPHA, BlendFactor::FACTOR_ONE_MINUS_SRC_ALPHA})
	, _keepLocal(false)
	, _isEnabled(true)
	, _lastUpdateTimeMs(0) {
}

Particle3DSystem::~Particle3DSystem() {
}

void Particle3DSystem::setEmitter(Particle3DEmitter* emitter)
{
    if (_emitter != emitter)
    {
        emitter->_particleSystem = this;
        _emitter = emitter;
    }
}

void Particle3DSystem::setRender(Particle3DRender* render)
{
    if (_render != render)
    {
        _render = render;
        _render->_particleSystem = this;
    }
}

void Particle3DSystem::addAffector(Particle3DAffector* affector)
{
    if (affector && std::find(_affectors.begin(), _affectors.end(), affector) == _affectors.end()){
        affector->_particleSystem = this;
        affector->ref();
        _affectors.push_back(affector);
    }
}

void Particle3DSystem::removeAffector(int index)
{
    LOG_FATAL_IF((unsigned int) index >= _affectors.size(), "wrong index");
    _affectors[index]->deref();
    _affectors.erase(_affectors.begin() + index);
}

void Particle3DSystem::removeAllAffector()
{
    //release all affectors
    for (auto it : _affectors) {
        it->deref();
    }
    _affectors.clear();
}

Particle3DAffector* Particle3DSystem::getAffector(int index)
{
	LOG_FATAL_IF(index >= (int)_affectors.size(), "wrong index");
    return _affectors[index];
}

void Particle3DSystem::update(p_nsecs_t timeMs) {
	if (_state != State::RUNNING)
		return;
	if (_lastUpdateTimeMs == 0) {
		_lastUpdateTimeMs = timeMs;
	}
	float delta = (timeMs - _lastUpdateTimeMs) / 1000.f;

	Particle3D *particle = _particlePool.getFirst();
	while (particle)
	{
		if (_emitter != nullptr)
		{
			_emitter->updateEmitter(particle, delta);
		}

		for (auto& it : _affectors) {
			it->updateAffector(particle, delta);
		}

		particle = _particlePool.getNext();
	}
}

void Particle3DSystem::render(graphic::GraphicContext* graphic, p_nsecs_t timeMs) {
	if (getAliveParticleCount() > 0 && _render != nullptr) {
	}
}
/*
void Particle3DSystem::draw(Renderer *renderer, const mat4 &transform, uint32_t flags) {
    if (getAliveParticleCount() && _render)
    {
        _render->render(renderer, transform, this);
    }
}
*/

void Particle3DSystem::setBlendFunc(const BlendFunc &blendFunc)
{
    _blend = blendFunc;
}

const BlendFunc &Particle3DSystem::getBlendFunc() const
{
    return _blend;
}

void Particle3DSystem::setParticleQuota( unsigned int quota )
{
    _particleQuota = quota;
}

unsigned int Particle3DSystem::getParticleQuota() const
{
    return _particleQuota;
}

void Particle3DSystem::setKeepLocal( bool keepLocal )
{
    _keepLocal = keepLocal;
}

void Particle3DSystem::setEnabled( bool enabled )
{
    _isEnabled = enabled;
}

} /* namespace graphic */
} /* namespace pola */
