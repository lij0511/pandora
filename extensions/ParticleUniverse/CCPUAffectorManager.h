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

#ifndef __CC_PU_PARTICLE_3D_AFFECTOR_MANAGER_H__
#define __CC_PU_PARTICLE_3D_AFFECTOR_MANAGER_H__

#include "CCPUScriptTranslator.h"
#include "CCPUAffector.h"
#include "CCPUAlignAffectorTranslator.h"
#include "CCPUBaseColliderTranslator.h"
#include "CCPUBaseForceAffectorTranslator.h"
#include "CCPUBoxColliderTranslator.h"
#include "CCPUCollisionAvoidanceAffectorTranslator.h"
#include "CCPUColorAffectorTranslator.h"
#include "CCPUFlockCenteringAffectorTranslator.h"
#include "CCPUForceFieldAffectorTranslator.h"
#include "CCPUGeometryRotatorTranslator.h"
#include "CCPUGravityAffectorTranslator.h"
#include "CCPUInterParticleColliderTranslator.h"
#include "CCPUJetAffectorTranslator.h"
#include "CCPULineAffectorTranslator.h"
#include "CCPULinearForceAffectorTranslator.h"
#include "CCPUParticleFollowerTranslator.h"
#include "CCPUPathFollowerTranslator.h"
#include "CCPUPlaneColliderTranslator.h"
#include "CCPURandomiserTranslator.h"
#include "CCPUScaleAffectorTranslator.h"
#include "CCPUScaleVelocityAffectorTranslator.h"
#include "CCPUSineForceAffectorTranslator.h"
#include "CCPUSphereColliderTranslator.h"
#include "CCPUTextureAnimatorTranslator.h"
#include "CCPUTextureRotatorTranslator.h"
#include "CCPUVelocityMatchingAffectorTranslator.h"
#include "CCPUVortexAffectorTranslator.h"

using namespace std;
namespace pola {
namespace graphic {

class PUAffectorManager
{
public:
    
    static PUAffectorManager* Instance();

    /**
     */
    PUScriptTranslator* getTranslator(const std::string &type);
    PUAffector* createAffector(const std::string &type);

    
public:
    PUAffectorManager();
    ~PUAffectorManager();

protected:

    PUAlignAffectorTranslator _alignAffectorTranslator;
    PUBaseColliderTranslator _baseColliderTranslator;
    PUBaseForceAffectorTranslator _baseForceAffectorTranslator;
    PUBoxColliderTranslator _boxColliderTranslator;
    PUCollisionAvoidanceAffectorTranslator _collisionAvoidanceAffectorTranstor;
    PUColorAffectorTranslator _colorAffectorTranslator; 
    PUFlockCenteringAffectorTranslator _flockCenteringAffectorTranslator;
    PUForceFieldAffectorTranslator _forceFieldAffectorTranslator;
    PUGeometryRotatorTranslator _geometryRotatorTranslator; 
    PUGravityAffectorTranslator _gravityAffectorTranslator;
    PUInterParticleColliderTranslator _interParticleColliderTranslator;
    PUJetAffectorTranslator _jetAffectorTranslator;
    PULineAffectorTranslator _lineAffectorTranslator;
    PULinearForceAffectorTranslator _linearForceAffectorTranslator;
    PUParticleFollowerTranslator _particleFollowerTranslator;
    PUPathFollowerTranslator _pathFollowerTranslator;
    PUPlaneColliderTranslator _planeColliderTranslator;
    PURandomiserTranslator _randomiserTranslator;
    PUScaleAffectorTranslator _scaleAffectorTranslator;
    PUScaleVelocityAffectorTranslator _scaleVelocityAffectorTranslator;
    PUSineForceAffectorTranslator _sineForceAffectorTranslator;
    PUSphereColliderTranslator _sphereColliderTranslator;
    PUTextureAnimatorTranslator _textureAnimatorTranslator;
    PUTextureRotatorTranslator _textureRotatorTranslator;
    PUVelocityMatchingAffectorTranslator _velocityMatchingAffectorTranslator;
    PUVortexAffectorTranslator _vortexAffectorTranslator;
};

} /* namespace graphic */
} /* namespace pola */


#endif 
