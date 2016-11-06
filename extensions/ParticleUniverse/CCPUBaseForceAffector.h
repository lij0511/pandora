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


#ifndef __CC_PU_PARTICLE_3D_BASE_FORCE_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_BASE_FORCE_AFFECTOR_H__

#include "pola/graphic/math/Math.h"
#include "CCPUAffector.h"

namespace pola {
namespace graphic {

class  PUBaseForceAffector : public PUAffector
{
public:
    enum ForceApplication
    {
        FA_AVERAGE,
        FA_ADD
    };

    // Constants
    static const vec3 DEFAULT_FORCE_VECTOR;
    static const ForceApplication DEFAULT_FORCE_APPL;

    /** 
    */
    const vec3& getForceVector() const;
    void setForceVector(const vec3& forceVector);

    /** 
    */
    ForceApplication getForceApplication() const;
    void setForceApplication(ForceApplication forceApplication);

    virtual void copyAttributesTo (PUAffector* affector) override;

public:
    PUBaseForceAffector();
    virtual ~PUBaseForceAffector();

protected:

    vec3 _forceVector;
    vec3 _scaledVector;
    ForceApplication _forceApplication;

};
} /* namespace graphic */
} /* namespace pola */

#endif
