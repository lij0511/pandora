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

#ifndef __CC_PU_PARTICLE_3D_ON_COUNT_OBSERVER_H__
#define __CC_PU_PARTICLE_3D_ON_COUNT_OBSERVER_H__

#include "pola/graphic/math/Math.h"
#include "CCPUObserver.h"
#include <vector>
#include <string>

namespace pola {
namespace graphic {

struct PUParticle3D;
class PUParticleSystem3D;

class PUOnCountObserver : public PUObserver
{
protected:
    unsigned int _count;
    unsigned int _threshold;
    PUComparisionOperator _compare;

public:

    static PUOnCountObserver* create();

    // Constants
    static const unsigned int DEFAULT_THRESHOLD;
    static const PUComparisionOperator DEFAULT_COMPARE;
    /** 
    */
    virtual void notifyStart (void) override;

    /** 
    */
    virtual bool observe (PUParticle3D* particle, float timeElapsed) override;

    /** 
    */
    unsigned int getThreshold(void) const {return _threshold;};
    void setThreshold(unsigned int threshold){_threshold = threshold;};

    /** 
    */
    PUComparisionOperator getCompare() const {return _compare;};
    void setCompare(PUComparisionOperator op){_compare = op;};

    virtual void copyAttributesTo (PUObserver* observer) override;

public:
    PUOnCountObserver(void);
    virtual ~PUOnCountObserver(void) {};
};

} /* namespace graphic */
} /* namespace pola */

#endif