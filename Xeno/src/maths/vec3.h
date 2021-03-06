#pragma once

#include <iostream>
#include <math.h>

namespace xeno { namespace maths {

	struct vec2;

	struct vec3
	{
		float x, y, z;
		
		vec3();
		vec3(const float& x, const float& y, const float& z);
		vec3(const vec2& other);

		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);

		vec3& operator +=(vec3& other);
		vec3& operator -=(vec3& other);
		vec3& operator *=(vec3& other);
		vec3& operator /=(vec3& other);

		bool operator ==(vec3& other);
		bool operator !=(vec3& other);

		float distance(const vec3& other) const;

		friend vec3 operator +(vec3 left, const vec3& right);
		friend vec3 operator -(vec3 left, const vec3& right);
		friend vec3 operator *(vec3 left, const vec3& right);
		friend vec3 operator /(vec3 left, const vec3& right);

		vec3 cross(const vec3& other) const;
		float dot(const vec3& other) const;
		float magnitude() const;
		vec3 normalize() const;

		friend std::ostream& operator <<(std::ostream& stream, const vec3& vector);
	};

} }
