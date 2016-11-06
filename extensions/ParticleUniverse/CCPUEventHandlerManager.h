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
#ifndef __CC_PU_PARTICLE_3D_EVENT_HANDLER_MANAGER_H__
#define __CC_PU_PARTICLE_3D_EVENT_HANDLER_MANAGER_H__

#include "CCPUScriptTranslator.h"
#include "CCPUEventHandler.h"
#include "CCPUDoAffectorEventHandlerTranslator.h"
#include "CCPUDoEnableComponentEventHandlerTranslator.h"
#include "CCPUDoExpireEventHandlerTranslator.h"
#include "CCPUDoFreezeEventHandlerTranslator.h"
#include "CCPUDoPlacementParticleEventHandlerTranslator.h"
#include "CCPUDoScaleEventHandlerTranslator.h"
#include "CCPUDoStopSystemEventHandlerTranslator.h"


namespace pola {
namespace graphic {
class PUEventHandlerManager
{
public:
    
    static PUEventHandlerManager* Instance();

    /**
     */
    PUScriptTranslator* getTranslator(const std::string &type);
    PUEventHandler* createEventHandler(const std::string &type);

    
public:

    PUEventHandlerManager();
    ~PUEventHandlerManager();

protected:

    PUDoAffectorEventHandlerTranslator _doAffectorEventHandlerTranslator;
    PUDoEnableComponentEventHandlerTranslator _doEnableComponentEventHandlerTranslator;
    PUDoExpireEventHandlerTranslator _doExpireEventHandlerTranslator;
    PUDoFreezeEventHandlerTranslator _doFreezeEventHandlerTranslator;
    PUDoPlacementParticleEventHandlerTranslator _doPlacementParticleEventHandlerTranslator;
    PUDoScaleEventHandlerTranslator _doScaleEventHandlerTranslator;
    PUDoStopSystemEventHandlerTranslator _doStopSystemEventHandlerTranslator;

};

} /* namespace graphic */
} /* namespace pola */


#endif 
