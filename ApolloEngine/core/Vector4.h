#pragma once

/**
*
* @file     Vector4.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Matrix4x4 template
*
*/

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
	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	//--------------------------------------------------------------------------------------
	Vector4(): x(0), y(0), z(0), w(0) {}

	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	/// 
	/// @param [in] Type construct values
	//--------------------------------------------------------------------------------------
	Vector4( Type _x, Type _y, Type _z, Type _w ) :x(_x), y(_y), z(_z), w(_w) {}

	//--------------------------------------------------------------------------------------
	/// @brief Copy operator
	/// 
	/// @param [in] rhs copy vector from rhs
	//--------------------------------------------------------------------------------------
	Vector4( const Vector4<Type> &rhs ): x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

	//--------------------------------------------------------------------------------------
	/// @brief Assign operator
	/// 
	/// @param [in] rhs Assign matrix4x4 from rhs
	/// 
	/// @return Self
	//--------------------------------------------------------------------------------------
	Vector4<Type>& operator = ( const Vector4<Type> &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;

		return *(this);
	}

	//--------------------------------------------------------------------------------------
	/// @brief Multiply operator
	/// 
	/// @param [in] val multiply value
	/// 
	/// @return Self
	//--------------------------------------------------------------------------------------
	Vector4<Type>& operator *= ( Type val ) const
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;

		return (*this);
	}

};

}
