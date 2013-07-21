#pragma once

/**
*
* @file     Vector3.h
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
class Vector3
{
public:
	Type x;
	Type y;
	Type z;
	
public:
	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	//--------------------------------------------------------------------------------------
	Vector3(): x(0), y(0), z(0) {}

	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	/// 
	/// @param [in] Type Assign to this vector
	//--------------------------------------------------------------------------------------
	Vector3( Type x, Type y, Type z ) :x(x), y(y), z(z) {}

	//--------------------------------------------------------------------------------------
	/// @brief Copy operator
	/// 
	/// @param [in] rhs Copy from
	//--------------------------------------------------------------------------------------
	Vector3( const Vector3<Type> &rhs ): x(rhs.x), y(rhs.y), z(rhs.z) {}

	//--------------------------------------------------------------------------------------
	/// @brief Assign operator
	/// 
	/// @param [in] rhs Assign vector3 from rhs
	/// 
	/// @return Self
	//--------------------------------------------------------------------------------------
	Vector3<Type>& operator = ( const Vector3<Type> &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *(this);
	}

	//--------------------------------------------------------------------------------------
	/// @brief Multiply operator
	/// 
	/// @param [in] val 
	/// 
	/// @return Self
	//--------------------------------------------------------------------------------------
	Vector3<Type>& operator *= ( Type val )
	{
		x *= val;
		y *= val;
		z *= val;
		
		return (*this);
	}

	//--------------------------------------------------------------------------------------
	/// @brief Comparison operator
	/// 
	/// @param [in] rhs compare from rhs
	/// 
	/// @return bool ( true: equal, false: not equal )
	//--------------------------------------------------------------------------------------
	bool operator == ( const Vector3<Type>& rhs ) const
	{
		if ( x == rhs.x &&
			y == rhs.y &&
			z == rhs.z )
			return true;
		else
			return false;    
	}

	//--------------------------------------------------------------------------------------
	/// @brief Subtract operator
	/// 
	/// @param [in] rhs Subtract rhs
	/// 
	/// @return Vector3
	//--------------------------------------------------------------------------------------
	Vector3<Type> operator - ( const Vector3<Type>& rhs ) const	
	{
		return Vector3<Type>( x - rhs.x, y - rhs.y, z - rhs.z );
	}
	
	//--------------------------------------------------------------------------------------
	/// @brief Cross product
	/// 
	/// @param [in] rhs Cross vector rhs
	/// 
	/// @return Vector3
	//--------------------------------------------------------------------------------------
	Vector3<Type> Cross( const Vector3<Type>& rhs ) const
	{
		return Vector3<Type>( y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x );
	}

	//--------------------------------------------------------------------------------------
	/// @brief Length
	///
	/// @return length
	//--------------------------------------------------------------------------------------
	Type Length()
	{
		Type sum = x * x + y * y + z * z;
		return sqrt( sum );
	}

	//--------------------------------------------------------------------------------------
	/// @brief Normalize vector
	//--------------------------------------------------------------------------------------
	void Normalize()
	{
		Type length = Length();    

		if (length != 0)
		{
			Type inv = 1 / length;

			x *= inv;
			y *= inv;
			z *= inv;    
		}
	}

};

}
