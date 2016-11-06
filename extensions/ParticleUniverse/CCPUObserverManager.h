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

#ifndef __CC_PU_PARTICLE_3D_OBSERVER_MANAGER_H__
#define __CC_PU_PARTICLE_3D_OBSERVER_MANAGER_H__

#include "CCPUScriptTranslator.h"
#include "CCPUObserver.h"
#include "CCPUOnClearObserverTranslator.h"
#include "CCPUOnCollisionObserverTranslator.h"
#include "CCPUOnCountObserverTranslator.h"
#include "CCPUOnEmissionObserverTranslator.h"
#include "CCPUOnEventFlagObserverTranslator.h"
#include "CCPUOnExpireObserverTranslator.h"
#include "CCPUOnPositionObserverTranslator.h"
#include "CCPUOnQuotaObserverTranslator.h"
#include "CCPUOnRandomObserverTranslator.h"
#include "CCPUOnTimeObserverTranslator.h"
#include "CCPUOnVelocityObserverTranslator.h"


namespace pola {
namespace graphic {
class PUObserverManager
{
public:
    
    static PUObserverManager* Instance();

    /**
     */
    PUScriptTranslator* getTranslator(const std::string &type);
    PUObserver* createObserver(const std::string &type);

    
public:

    PUObserverManager();
    ~PUObserverManager();

protected:

    PUOnClearObserverTranslator _onClearObserverTranslator;
    PUOnCollisionObserverTranslator _onCollisionObserverTranslator;
    PUOnCountObserverTranslator _onCountObserverTranslator;
    PUOnEmissionObserverTranslator _onEmissionObserverTranslator;
    PUOnEventFlagObserverTranslator _onEventFlagObserverTranslator;
    PUOnExpireObserverTranslator _onExpireObserverTranslator;
    PUOnPositionObserverTranslator _onPositionObserverTranslator;
    PUOnQuotaObserverTranslator _onQuotaObserverTranslator;
    PUOnRandomObserverTranslator _onRandomObserverTranslator;
    PUOnTimeObserverTranslator _onTimeObserverTranslator;
    PUOnVelocityObserverTranslator _onVelocityObserverTranslator;
};

} /* namespace graphic */
} /* namespace pola */


#endif 
