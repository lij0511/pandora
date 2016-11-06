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

#include "CCPUAffectorManager.h"
#include "CCPUAlignAffector.h"
#include "CCPUBaseCollider.h"
#include "CCPUBaseForceAffector.h"
#include "CCPUBoxCollider.h"
#include "CCPUCollisionAvoidanceAffector.h"
#include "CCPUColorAffector.h"
#include "CCPUFlockCenteringAffector.h"
#include "CCPUForceFieldAffector.h"
#include "CCPUGeometryRotator.h"
#include "CCPUGravityAffector.h"
#include "CCPUInterParticleCollider.h"
#include "CCPUJetAffector.h"
#include "CCPULineAffector.h"
#include "CCPULinearForceAffector.h"
#include "CCPUParticleFollower.h"
#include "CCPUPathFollower.h"
#include "CCPUPlaneCollider.h"
#include "CCPURandomiser.h"
#include "CCPUScaleAffector.h"
#include "CCPUScaleVelocityAffector.h"
#include "CCPUSineForceAffector.h"
#include "CCPUSphereCollider.h"
#include "CCPUTextureAnimator.h"
#include "CCPUTextureRotator.h"
#include "CCPUVelocityMatchingAffector.h"
#include "CCPUVortexAffector.h"

namespace pola {
namespace graphic {
PUAffectorManager::PUAffectorManager()
{
    
}

PUAffectorManager::~PUAffectorManager()
{
    
}

PUAffectorManager* PUAffectorManager::Instance()
{
    static PUAffectorManager pam;
    return &pam;
}

PUScriptTranslator* PUAffectorManager::getTranslator( const std::string &type )
{
    if (type == "Align"){
        return &_alignAffectorTranslator;
    }else if (type == "Dummy02"){
        return &_baseColliderTranslator;
    }else if (type == "Dummy01"){
        return &_baseForceAffectorTranslator;
    }else if (type == "BoxCollider"){
        return &_boxColliderTranslator;
    }else if (type == "CollisionAvoidance"){
        return &_collisionAvoidanceAffectorTranstor;
    }else if (type == "Colour"){
        return &_colorAffectorTranslator;
    }else if (type == "FlockCentering"){
        return &_flockCenteringAffectorTranslator;
    }else if (type == "ForceField"){
        return &_forceFieldAffectorTranslator;
    }else if (type == "GeometryRotator"){
        return &_geometryRotatorTranslator;
    }else if (type == "Gravity"){
        return &_gravityAffectorTranslator;
    }else if (type == "InterParticleCollider"){
        return &_interParticleColliderTranslator;
    }else if (type == "Jet"){
        return &_jetAffectorTranslator;
    }else if (type == "Line"){
        return &_lineAffectorTranslator;
    }else if (type == "LinearForce"){
        return &_linearForceAffectorTranslator;
    }else if (type == "ParticleFollower"){
        return &_particleFollowerTranslator;
    }else if (type == "PathFollower"){
        return &_pathFollowerTranslator;
    }else if (type == "PlaneCollider"){
        return &_planeColliderTranslator;
    }else if (type == "Randomiser"){
        return &_randomiserTranslator;
    }else if (type == "Scale"){
        return &_scaleAffectorTranslator;
    }else if (type == "ScaleVelocity"){
        return &_scaleVelocityAffectorTranslator;
    }else if (type == "SineForce"){
        return &_sineForceAffectorTranslator;
    }else if (type == "SphereCollider"){
        return &_sphereColliderTranslator;
    }else if (type == "TextureAnimator"){
        return &_textureAnimatorTranslator;
    }else if (type == "TextureRotator"){
        return &_textureRotatorTranslator;
    }else if (type == "VelocityMatching"){
        return &_velocityMatchingAffectorTranslator;
    }else if (type == "Vortex"){
        return &_vortexAffectorTranslator;
    }
    return nullptr;
}

PUAffector* PUAffectorManager::createAffector( const std::string &type )
{
    if (type == "Align"){
        return PUAlignAffector::create();
    }else if (type == "Dummy02"){
        return nullptr;
    }else if (type == "Dummy01"){
        return nullptr;
    }else if (type == "BoxCollider"){
        return PUBoxCollider::create();
    }else if (type == "CollisionAvoidance"){
        return PUCollisionAvoidanceAffector::create();
    }else if (type == "Colour"){
        return PUColorAffector::create();
    }else if (type == "FlockCentering"){
        return PUFlockCenteringAffector::create();
    }else if (type == "ForceField"){
        return PUForceFieldAffector::create();
    }else if (type == "GeometryRotator"){
        return PUGeometryRotator::create();
    }else if (type == "Gravity"){
        return PUGravityAffector::create();
    }else if (type == "InterParticleCollider"){
        return PUParticle3DInterParticleCollider::create();
    }else if (type == "Jet"){
        return PUJetAffector::create();
    }else if (type == "Line"){
        return PULineAffector::create();
    }else if (type == "LinearForce"){
        return PULinearForceAffector::create();
    }else if (type == "ParticleFollower"){
        return PUParticleFollower::create();
    }else if (type == "PathFollower"){
        return PUPathFollower::create();
    }else if (type == "PlaneCollider"){
        return PUPlaneCollider::create();
    }else if (type == "Randomiser"){
        return PURandomiser::create();
    }else if (type == "Scale"){
        return PUScaleAffector::create();
    }else if (type == "ScaleVelocity"){
        return PUScaleVelocityAffector::create();
    }else if (type == "SineForce"){
        return PUSineForceAffector::create();
    }else if (type == "SphereCollider"){
        return PUSphereCollider::create();
    }else if (type == "TextureAnimator"){
        return PUTextureAnimator::create();
    }else if (type == "TextureRotator"){
        return PUTextureRotator::create();
    }else if (type == "VelocityMatching"){
        return PUVelocityMatchingAffector::create();
    }else if (type == "Vortex"){
        return PUVortexAffector::create();
    }
    return nullptr;
}

} /* namespace graphic */
} /* namespace pola */
