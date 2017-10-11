/*************************************************************************/
/*  btRayShape.h                                                        */
/*  Author: AndreaCatania                                                */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2017 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2017 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "btRayShape.h"
#include "math/math_funcs.h"

btRayShape::btRayShape(btScalar p_length)
	: btConvexInternalShape(), m_shapeAxis(0, 0, 1), m_length(p_length) {
	m_shapeType = CUSTOM_CONVEX_SHAPE_TYPE;
}

btRayShape::~btRayShape() {
}

btVector3 btRayShape::localGetSupportingVertexWithoutMargin(const btVector3 &vec) const {
	if (vec.z() > 0)
		return m_shapeAxis * m_length;
	else
		return btVector3(0, 0, 0);
}

void btRayShape::batchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3 *vectors, btVector3 *supportVerticesOut, int numVectors) const {
	for (int i = 0; i < numVectors; ++i) {
		if (vectors[i].z() > 0) {
			supportVerticesOut[i] = m_shapeAxis * m_length;
		} else {
			supportVerticesOut[i].setZero();
		}
	}
}

void btRayShape::getAabb(const btTransform &t, btVector3 &aabbMin, btVector3 &aabbMax) const {
#define MARGIN 0.0005
	btVector3 localAabbMin(0, 0, 0);
	btVector3 localAabbMax(m_shapeAxis * m_length);
	btTransformAabb(localAabbMin, localAabbMax, MARGIN, t, aabbMin, aabbMax);
}

void btRayShape::setLocalScaling(const btVector3 &scaling) {
	const btScalar old_zScale(m_localScaling[2]);
	btConvexInternalShape::setLocalScaling(scaling);

	const btScalar unscaledLength = m_length / old_zScale;
	m_length = unscaledLength * m_localScaling[2];
}

void btRayShape::calculateLocalInertia(btScalar mass, btVector3 &inertia) const {
	inertia.setZero();
}
