/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef __CC_PU_PARTICLE_3D_SLAVE_EMITTER_H__
#define __CC_PU_PARTICLE_3D_SLAVE_EMITTER_H__

#include "CCPUEmitter.h"
#include "CCPUListener.h"

namespace pola {
namespace graphic {
//FIXME
class  PUSlaveEmitter : public PUEmitter, public PUListener
{
public:

    static PUSlaveEmitter* create();

    /** 
    */
    const std::string& getMasterTechniqueName(void) const;

    /** 
    */
    void setMasterTechniqueName(const std::string& masterTechniqueName);

    /** 
    */
    const std::string& getMasterEmitterName(void) const;

    /** See ParticleEmitter.
    */
    virtual void initParticlePosition(PUParticle3D* particle) override;

    /** See ParticleEmitter.
    */
    virtual void initParticleDirection(PUParticle3D* particle) override;

    /** See ParticleEmitter.
    */
    virtual void prepare() override;

    /** See ParticleEmitter.
    */
    virtual void unPrepare() override;

    /** See ParticleEmitter.
    */
    virtual void notifyStart (void) override;

    /** Initialise the emitted particle. This means that its position is set.
    */
    virtual void particleEmitted(PUParticleSystem3D* particleSystem, PUParticle3D* particle) override;

    /** No implementation.
    */
    virtual void particleExpired(PUParticleSystem3D* particleSystem, PUParticle3D* particle) override{};

    /** 
    */
    void setMasterEmitterName(const std::string& masterEmitterName);

    virtual PUSlaveEmitter* clone() override;
    virtual void copyAttributesTo (PUEmitter* emitter) override;

public:
    PUSlaveEmitter(void);
    virtual ~PUSlaveEmitter(void){};

protected:

    PUParticle3D* _masterParticle;
    std::string _masterTechniqueName;
    std::string _masterEmitterName;
    vec3 _masterPosition;
    vec3 _masterDirection;
    bool _masterEmitterNameSet;
};
} /* namespace graphic */
} /* namespace pola */

#endif
