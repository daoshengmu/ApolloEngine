#pragma once

/**
*
* @file     Vector2.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Vector2 template
*
*/

namespace Apollo
{

template<class Type>
class Vector2
{
public:
	Type x;
	Type y;

public:
	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	//--------------------------------------------------------------------------------------
	Vector2(): x(0), y(0) {}

	//--------------------------------------------------------------------------------------
	/// @brief Constructor
	/// 
	/// @param [in] Type Assign to this vector
	//--------------------------------------------------------------------------------------
	Vector2( Type x, Type y ) :x(x), y(y) {}

	//--------------------------------------------------------------------------------------
	/// @brief Copy operator
	/// 
	/// @param [in] rhs Copy from
	//--------------------------------------------------------------------------------------
	Vector2( const Vector2<Type> &rhs ): x(rhs.x), y(rhs.y) {}

	//--------------------------------------------------------------------------------------
	/// @brief Assign operator
	/// 
	/// @param [in] rhs Assign vector3 from rhs
	/// 
	/// @return Self
	//--------------------------------------------------------------------------------------
	Vector2<Type>& operator = ( const Vector2<Type> &rhs )
	{
		x = rhs.x;
		y = rhs.y;
	
		return *(this);
	}

	//--------------------------------------------------------------------------------------
	/// @brief Length
	///
	/// @return length
	//--------------------------------------------------------------------------------------
	Type Length()
	{
		Type sum = x * x + y * y;
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
		}
	}

};

}
