#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

#include "vec2.h"
#include "vec3.h"
#include "mat4.h"

namespace mb { namespace maths {

	const Mat4 translate(const Mat4& mat, const Vec3& translateVec)
	{
		Mat4 translationMat;
		translationMat[0][3] = translateVec.x;
		translationMat[1][3] = translateVec.y;
		translationMat[2][3] = translateVec.z;

		return mat * translationMat;
	}

	const Mat4 scale(const Mat4& mat, const Vec3& scaleVec)
	{
		Mat4 scaleMat;
		scaleMat[0][0] = scaleVec.x;
		scaleMat[1][1] = scaleVec.y;
		scaleMat[2][2] = scaleVec.z;

		return mat * scaleMat;
	}

	const Mat4 rotate(const Mat4& mat, float theta, const Vec3& axis)
	{
		Vec3 normAxis = axis.Normalize();
		Mat4 rotationMat;
		rotationMat[0][0] = cos(theta) + pow(normAxis.x, 2) * (1 - cos(theta));
		rotationMat[0][1] = normAxis.x * normAxis.y * (1 - cos(theta)) - normAxis.z * sin(theta);
		rotationMat[0][2] = normAxis.x * normAxis.z * (1 - cos(theta)) + normAxis.y * sin(theta);
		rotationMat[1][0] = normAxis.y * normAxis.x * (1 - cos(theta)) + normAxis.z * sin(theta);
		rotationMat[1][1] = cos(theta) + pow(normAxis.y, 2) * (1 - cos(theta));
		rotationMat[1][2] = normAxis.y * normAxis.z * (1 - cos(theta)) - normAxis.x * sin(theta);
		rotationMat[2][0] = normAxis.z * normAxis.x * (1 - cos(theta)) - normAxis.y * sin(theta);
		rotationMat[2][1] = normAxis.z * normAxis.y * (1 - cos(theta)) - normAxis.x * sin(theta);
		rotationMat[2][2] = cos(theta) + pow(normAxis.z, 2) * (1 - cos(theta));

		return mat * rotationMat;
	}

	const Mat4 ortho(float left, float right, float bottom, float top, float near, float far)
	{
		Mat4 result;
		result[0][0] = 2 / (right - left);
		result[1][1] = 2 / (top - bottom);
		result[2][2] = -2 / (far - near);
		result[0][3] = -(right + left) / (right - left);
		result[1][3] = -(top + bottom) / (top - bottom);
		result[2][3] = -(far + near) / (far - near);

		return result;
	}

	float radians(float degrees)
	{
		return degrees / 180 * M_PI;
	}

} }