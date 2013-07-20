
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

	Quaternion<Type>& operator = ( const Quaternion<Type> &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;

		return *(this);
	}
		
	Quaternion<Type> operator * ( const Quaternion<Type>& q ) const
	{    
		return Quaternion<Type>( y * q.z - z * q.y + x * q.w + w * q.x,
			z * q.x - x * q.z + y * q.w + w * q.y,
			x * q.y - y * q.x + z * q.w + w * q.z,
			w * q.w - x * q.x - y * q.y - z * q.z );
	} 

// 	void RotateAroundAxis( const Vector3<Type> &axis, Type angle )
// 	{
// 		w = cos(angle/2);
// 		x = ( axis.x * sin(angle/2));
// 		y = ( axis.y * sin(angle/2));
// 		z = ( axis.z * sin(angle/2));
// 	}

	Quaternion<Type>& fromAngleAxis( Type angle, const Vector3<Type>& axis)
	{
		const Type fHalfAngle = DEGREE_TO_RADIAN( 0.5f * angle );
		const Type fSin = sinf(fHalfAngle);
		w = cosf(fHalfAngle);
		x = fSin*axis.x;
		y = fSin*axis.y;
		z = fSin*axis.z;

		return *this;
	}

	void Inverse()
	{
		Type d = x*x + y*y + z*z + w*w;    

		Type inv = 1 / d;

		x = -x * inv;
		y = -y * inv;
		z = -z * inv;
		w =  w * inv;    
	}

	Vector3<Type> TransformVector3D(const Vector3<Type>& v) const
	{
		Quaternion<Type> inv(x, y, z, w);
		inv.Inverse();

		Quaternion<Type> input(v.x, v.y, v.z, 0);

		Quaternion<Type> output = (*this) * input * inv;

		return Vector3<Type>(output.x, output.y, output.z);
	}
	
};

}