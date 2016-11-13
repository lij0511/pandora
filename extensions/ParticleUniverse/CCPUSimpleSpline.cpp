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

#include "CCPUSimpleSpline.h"
#include "pola/log/Log.h"

namespace pola {
namespace graphic {
//---------------------------------------------------------------------
PUSimpleSpline::PUSimpleSpline()
{
    // Set up matrix
    // Hermite polynomial
    _coeffs.data[0] = 2;
    _coeffs.data[1] = -2;
    _coeffs.data[2] = 1;
    _coeffs.data[3] = 1;
    _coeffs.data[4] = -3;
    _coeffs.data[5] = 3;
    _coeffs.data[6] = -2;
    _coeffs.data[7] = -1;
    _coeffs.data[8] = 0;
    _coeffs.data[9] = 0;
    _coeffs.data[10] = 1;
    _coeffs.data[11] = 0;
    _coeffs.data[12] = 1;
    _coeffs.data[13] = 0;
    _coeffs.data[14] = 0;
    _coeffs.data[15] = 0;

    _autoCalc = true;
}
//---------------------------------------------------------------------
PUSimpleSpline::~PUSimpleSpline()
{
}
//---------------------------------------------------------------------
void PUSimpleSpline::addPoint(const vec3& p)
{
    _points.push_back(p);
    if (_autoCalc)
    {
        recalcTangents();
    }
}
//---------------------------------------------------------------------
vec3 PUSimpleSpline::interpolate(float t) const
{
    // Currently assumes points are evenly spaced, will cause velocity
    // change where this is not the case
    // TODO: base on arclength?


    // Work out which segment this is in
    float fSeg = t * (_points.size() - 1);
    unsigned int segIdx = (unsigned int)fSeg;
    // Apportion t 
    t = fSeg - segIdx;

    return interpolate(segIdx, t);

}
//---------------------------------------------------------------------
vec3 PUSimpleSpline::interpolate(unsigned int fromIndex, float t) const
{
    // Bounds check
    LOG_FATAL_IF(fromIndex >= _points.size(), "fromIndex out of bounds");

    if ((fromIndex + 1) == _points.size())
    {
        // Duff request, cannot blend to nothing
        // Just return source
        return _points[fromIndex];

    }

    // Fast special cases
    if (t == 0.0f)
    {
        return _points[fromIndex];
    }
    else if(t == 1.0f)
    {
        return _points[fromIndex + 1];
    }

    // Real interpolation
    // Form a vector of powers of t
    float t2, t3;
    t2 = t * t;
    t3 = t2 * t;
    vec4 powers(t3, t2, t, 1);


    // Algorithm is ret = powers * mCoeffs * Matrix4(point1, point2, tangent1, tangent2)
    const vec3& point1 = _points[fromIndex];
    const vec3& point2 = _points[fromIndex+1];
    const vec3& tan1 = _tangents[fromIndex];
    const vec3& tan2 = _tangents[fromIndex+1];
    mat4 pt;

    pt.data[0] = point1.x;
    pt.data[1] = point1.y;
    pt.data[2] = point1.z;
    pt.data[3] = 1.0f;
    pt.data[4] = point2.x;
    pt.data[5] = point2.y;
    pt.data[6] = point2.z;
    pt.data[7] = 1.0f;
    pt.data[8] = tan1.x;
    pt.data[9] = tan1.y;
    pt.data[10] = tan1.z;
    pt.data[11] = 1.0f;
    pt.data[12] = tan2.x;
    pt.data[13] = tan2.y;
    pt.data[14] = tan2.z;
    pt.data[15] = 1.0f;

    vec4 ret = pt * _coeffs * powers;


    return vec3(ret.x, ret.y, ret.z);




}
//---------------------------------------------------------------------
void PUSimpleSpline::recalcTangents(void)
{
    // Catmull-Rom approach
    // 
    // tangent[i] = 0.5 * (point[i+1] - point[i-1])
    //
    // Assume endpoint tangents are parallel with line with neighbour

    size_t i, numPoints;
    bool isClosed;

    numPoints = _points.size();
    if (numPoints < 2)
    {
        // Can't do anything yet
        return;
    }

    // Closed or open?
    if (_points[0] == _points[numPoints-1])
    {
        isClosed = true;
    }
    else
    {
        isClosed = false;
    }

    _tangents.resize(numPoints);



    for(i = 0; i < numPoints; ++i)
    {
        if (i ==0)
        {
            // Special case start
            if (isClosed)
            {
                // Use numPoints-2 since numPoints-1 is the last point and == [0]
                _tangents[i] = 0.5 * (_points[1] - _points[numPoints-2]);
            }
            else
            {
                _tangents[i] = 0.5 * (_points[1] - _points[0]);
            }
        }
        else if (i == numPoints-1)
        {
            // Special case end
            if (isClosed)
            {
                // Use same tangent as already calculated for [0]
                _tangents[i] = _tangents[0];
            }
            else
            {
                _tangents[i] = 0.5 * (_points[i] - _points[i-1]);
            }
        }
        else
        {
            _tangents[i] = 0.5 * (_points[i+1] - _points[i-1]);
        }

    }



}
//---------------------------------------------------------------------
const vec3& PUSimpleSpline::getPoint(unsigned short index) const
{
	LOG_FATAL_IF (index >= _points.size(), "Point index is out of bounds!!");

    return _points[index];
}
//---------------------------------------------------------------------
unsigned short PUSimpleSpline::getNumPoints(void) const
{
    return (unsigned short)_points.size();
}
//---------------------------------------------------------------------
void PUSimpleSpline::clear(void)
{
    _points.clear();
    _tangents.clear();
}
//---------------------------------------------------------------------
void PUSimpleSpline::updatePoint(unsigned short index, const vec3& value)
{
	LOG_FATAL_IF (index >= _points.size(),  "Point index is out of bounds!!");

    _points[index] = value;
    if (_autoCalc)
    {
        recalcTangents();
    }
}
//---------------------------------------------------------------------
void PUSimpleSpline::setAutoCalculate(bool autoCalc)
{
    _autoCalc = autoCalc;
}
} /* namespace graphic */
} /* namespace pola */
