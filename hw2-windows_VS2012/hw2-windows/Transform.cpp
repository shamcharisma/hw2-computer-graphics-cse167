// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	// YOUR CODE FOR HW1 HERE
	vec3 normalAxis = glm::normalize(axis);
	float radians = ((2 * pi) / 360) * degrees;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	mat3 xmat(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
	mat3 ymat(x*x, x*y, x*z, x*y, y*y, y*z, x*z, y*z, z*z);
	mat3 zmat(0.0, z, -y, -z, 0.0, x, y, -x, 0.0);

	mat3 rotMat((cos(radians)*xmat) + ((1 - cos(radians))*ymat) + (sin(radians)*(zmat)));
	return rotMat;
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
	mat3 rotMat = rotate(degrees, up);
	eye = rotMat * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 unit = glm::cross(eye, up);
	vec3 unitNormal = glm::normalize(unit);

	mat3 rotMat = rotate(degrees, unitNormal);
	eye = (rotMat * eye);
	up = glm::normalize(rotMat * up);

	int dot1 = glm::dot(eye, up);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
	vec3 w = glm::normalize(eye - center);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	mat4 transformMat = mat4(u.x, u.y, u.z, -glm::dot(u, eye),
		v.x, v.y, v.z, -glm::dot(v, eye),
		w.x, w.y, w.z, -glm::dot(w, eye),
		0, 0, 0, 1.0f);
	return transformMat;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float yScale = 1.0F / tan(glm::radians(fovy) / 2);
	float xScale = yScale / aspect;
	float range = zNear - zFar;
	float a = ((zNear + zFar) / range);
	float b = (2 * zNear * zFar) / range;

	mat4 transformMat = mat4(xScale, 0.0, 0.0, 0.0,
		0.0, yScale, 0.0, 0.0,
		0.0, 0.0, a, -1.0,
		0.0, 0.0, b, 0.0);

	return transformMat;
}


mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 scaleMat = mat4(sx, 0.0, 0.0, 0.0,
		0.0, sy, 0.0, 0.0,
		0.0, 0.0, sz, 0.0,
		0.0, 0.0, 0.0, 1.0);

	return scaleMat;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	mat4 translateMat = mat4(1.0, 0.0, 0.0, tx,
		0.0, 1.0, 0.0, ty,
		0.0, 0.0, 1.0, tz,
		0.0, 0.0, 0.0, 1.0);

	return translateMat;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
