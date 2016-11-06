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

#ifndef __CC_PU_PARTICLE_3D_EMITTER_MANAGER_H__
#define __CC_PU_PARTICLE_3D_EMITTER_MANAGER_H__

#include "CCPUScriptTranslator.h"
#include "CCPUEmitter.h"
#include "CCPUBoxEmitterTranslator.h"
#include "CCPUCircleEmitterTranslator.h"
#include "CCPULineEmitterTranslator.h"
#include "CCPUMeshSurfaceEmitterTranslator.h"
#include "CCPUPointEmitterTranslator.h"
#include "CCPUPositionEmitterTranslator.h"
#include "CCPUSlaveEmitterTranslator.h"
#include "CCPUSphereSurfaceEmitterTranslator.h"

using namespace std;
namespace pola {
namespace graphic {

class PUEmitterManager
{
public:
    
    static PUEmitterManager* Instance();

    /**
     */
    PUScriptTranslator* getTranslator(const std::string &type);
    PUEmitter* createEmitter(const std::string &type);

    
public:
    PUEmitterManager();
    ~PUEmitterManager();

protected:

    CCPUBoxEmitterTranslator _boxEmitterTranlator;
    PUCircleEmitterTranslator _circleEmitterTranlator;
    PULineEmitterTranslator _lineEmitterTranlator;
    PUMeshSurfaceEmitterTranslator _meshSurfaceEmitterTranlator;
    PUPointEmitterTranslator _pointEmitterTranlator;
    PUPositionEmitterTranslator _positionEmitterTranlator;
    PUSlaveEmitterTranslator _slaveEmitterTranlator;
    PUSphereSurfaceEmitterTranslator _sphereSurfaceEmitterTranlator;
};

} /* namespace graphic */
} /* namespace pola */


#endif 
