
#pragma once

namespace Apollo
{
template <class Type>
class Quaternion
{
public:
	Type x;
	Type y;
	Type z;
	Type w;

public:
	Quaternion() :x(0), y(0), z(0), w(1) {}
	Quaternion( const Quaternion<Type>& rhs )
		:x(rhs.x),
		y(rhs.y),
		z(rhs.z),
		w(rhs.w)
	{}

	Quaternion(  Type _x,  Type _y,  Type _z,  Type _w ) 
		:x(_x),
		y(_y),
		z(_z),
		w(_w)
	{

	}

	Matrix4x4<Type> ConvertToMatrix4() const
	{
		Matrix4x4<Type> out;

		Type *pItems = out.GetItems();

		pItems[ 4 * 0 + 0 ] = 1 - 2 * ( y*y + z*z );
		pItems[ 4 * 0 + 1 ] = 2 * ( x*y + w*z );
		pItems[ 4 * 0 + 2 ] = 2 * ( x*z - w*y );
		pItems[ 4 * 0 + 3 ] = 0;

		pItems[ 4 * 1 + 0 ] = 2 * ( x*y - w*z );
		pItems[ 4 * 1 + 1 ] = 1 - 2 * ( x*x + z*z );
		pItems[ 4 * 1 + 2 ] = 2 * ( y*z + w*x );
		pItems[ 4 * 1 + 3 ] = 0;

		pItems[ 4 * 2 + 0 ] = 2 * ( x*z + w*y );
		pItems[ 4 * 2 + 1 ] = 2 * ( y*z - w*x );
		pItems[ 4 * 2 + 2 ] = 1 - 2 * ( x*x + y*y );
		pItems[ 4 * 2 + 3 ] = 0;

		pItems[ 4 * 3 + 0 ] = 0;
		pItems[ 4 * 3 + 1 ] = 0;
		pItems[ 4 * 3 + 2 ] = 0;
		pItems[ 4 * 3 + 3 ] = 1;

		return out;
	}

	Quaternion& operator *= ( const Quaternion<Type>& q )
	{
		Type X,Y,Z,W;

		X = y * q.z - z * q.y + x * q.w + w * q.x;

		Y = z * q.x - x * q.z + y * q.w + w * q.y;

		Z = x * q.y - y * q.x + z * q.w + w * q.z;

		W = w * q.w - x * q.x - y * q.y - z * q.z;

		x = X;
		y = Y;
		z = Z;
		w = W;

		return (*this);
	}
};

}