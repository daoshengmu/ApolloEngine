#pragma once

namespace Apollo
{
template<class Type>
class Vector3
{
public:
	Type x;
	Type y;
	Type z;

public:
	Vector3(): x(0), y(0), z(0) {}
	Vector3( Type x, Type y, Type z ) :x(x), y(y), z(z) {}

	Vector3( const Vector3<Type> &rhs ): x(rhs.x), y(rhs.y), z(rhs.z) {}

	Vector3<Type>& operator = ( const Vector3<Type> &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *(this);
	}

	Vector3<Type> operator *= ( Type val )
	{
		x *= val;
		y *= val;
		z *= val;
		
		return (*this);
	}

};

}
