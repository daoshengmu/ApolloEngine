#pragma once

namespace Apollo
{
template<class Type>
class Vector4
{
public:
	Type x;
	Type y;
	Type z;
	Type w;

public:
	Vector4(): x(0), y(0), z(0), w(0) {}
	Vector4( Type _x, Type _y, Type _z, Type _w ) :x(_x), y(_y), z(_z), w(_w) {}

	Vector4( const Vector4<Type> &rhs ): x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

	Vector4<Type>& operator = ( const Vector4<Type> &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;

		return *(this);
	}

	Vector4<Type> operator *= ( Type val ) const
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;

		return (*this);
	}

};

}
