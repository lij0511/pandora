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
	, _isEnabled(true) {
}

Particle3DSystem::~Particle3DSystem() {
}

void Particle3DSystem::setEmitter(Particle3DEmitter* emitter)
{
    if (_emitter != emitter)
    {
        CC_SAFE_RELEASE(_emitter);
        emitter->_particleSystem = this;
        _emitter = emitter;
        CC_SAFE_RETAIN(_emitter);
    }
}

void Particle3DSystem::setRender(Particle3DRender* render)
{
    if (_render != render)
    {
        CC_SAFE_RELEASE(_render);
        _render = render;
        _render->_particleSystem = this;
        CC_SAFE_RETAIN(_render);
    }
}

void Particle3DSystem::addAffector(Particle3DAffector* affector)
{
    if (affector && std::find(_affectors.begin(), _affectors.end(), affector) == _affectors.end()){
        affector->_particleSystem = this;
        affector->retain();
        _affectors.push_back(affector);
    }
}

void Particle3DSystem::removeAffector(int index)
{
    LOG_FATAL_IF((unsigned int) index >= _affectors.size(), "wrong index");
    _affectors.erase(_affectors.begin() + index);
}

void Particle3DSystem::removeAllAffector()
{
    //release all affectors
    for (auto it : _affectors) {
        it->release();
    }
    _affectors.clear();
}

Particle3DAffector* Particle3DSystem::getAffector(int index)
{
	LOG_FATAL_IF(index >= (int)_affectors.size(), "wrong index");
    return _affectors[index];
}

void Particle3DSystem::update(float delta)
{
    if (_state != State::RUNNING)
        return;

    Particle3D *particle = _particlePool.getFirst();
    while (particle)
    {
        if (_emitter)
        {
            _emitter->updateEmitter(particle, delta);
        }

        for (auto& it : _affectors) {
            it->updateAffector(particle, delta);
        }

        particle = _particlePool.getNext();
    }
}

void Particle3DSystem::draw(Renderer *renderer, const mat4 &transform, uint32_t flags)
{
    if (getAliveParticleCount() && _render)
    {
        _render->render(renderer, transform, this);
    }
}

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
