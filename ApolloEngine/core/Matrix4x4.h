
#pragma once

//#include "Vector3.h"

namespace Apollo
{
template<class Type>
class Quaternion;

template<class Type>
class Matrix4x4
{
public:
	Matrix4x4() 
	{
		 SetIdentity();
	}

	Matrix4x4( const Matrix4x4<Type> &rhs)
	{
		const Type* pRHSItems = rhs.GetItems();

		memcpy( (void*)_items, (const void*)pRHSItems, sizeof(_items) );
	}

	Matrix4x4( 
		Type m00, Type m01, Type m02, Type m03,
		Type m10, Type m11, Type m12, Type m13,
		Type m20, Type m21, Type m22, Type m23,
		Type m30, Type m31, Type m32, Type m33 )
	{
		_items[0*4+0] = m00; _items[0*4+1] = m01; _items[0*4+2] = m02; _items[0*4+3] = m03;
		_items[1*4+0] = m10; _items[1*4+1] = m11; _items[1*4+2] = m12; _items[1*4+3] = m13;
		_items[2*4+0] = m20; _items[2*4+1] = m21; _items[2*4+2] = m22; _items[2*4+3] = m23;
		_items[3*4+0] = m30; _items[3*4+1] = m31; _items[3*4+2] = m32; _items[3*4+3] = m33;
	}

	void SetItems( 
		Type m00, Type m01, Type m02, Type m03,
		Type m10, Type m11, Type m12, Type m13,
		Type m20, Type m21, Type m22, Type m23,
		Type m30, Type m31, Type m32, Type m33 )
	{
		_items[0*4+0] = m00; _items[0*4+1] = m01; _items[0*4+2] = m02; _items[0*4+3] = m03;
		_items[1*4+0] = m10; _items[1*4+1] = m11; _items[1*4+2] = m12; _items[1*4+3] = m13;
		_items[2*4+0] = m20; _items[2*4+1] = m21; _items[2*4+2] = m22; _items[2*4+3] = m23;
		_items[3*4+0] = m30; _items[3*4+1] = m31; _items[3*4+2] = m32; _items[3*4+3] = m33;
	}

	void SetIdentity()
	{
		memcpy( _items, &GetIdentity(), sizeof(_items) );
	}

	//--------------------------------------------------------------------------
	/// @brief Transpose current matrix
	/// 
	/// @param [in] pMtx Assign martix ptr transpose to this
	//--------------------------------------------------------------------------
	void AssignTranspose( const Matrix4x4<Type>& matrix )
	{
		const Type *lpValue = matrix.GetItems();

		_items[0*4+0] = lpValue[0*4+0];
		_items[1*4+1] = lpValue[1*4+1];
		_items[2*4+2] = lpValue[2*4+2];
		_items[3*4+3] = lpValue[3*4+3];

		_items[0*4+1] = lpValue[1*4+0];
		_items[1*4+0] = lpValue[0*4+1];

		_items[0*4+2] = lpValue[2*4+0];
		_items[2*4+0] = lpValue[0*4+2];

		_items[0*4+3] = lpValue[3*4+0];
		_items[3*4+0] = lpValue[0*4+3];

		_items[1*4+2] = lpValue[2*4+1];
		_items[2*4+1] = lpValue[1*4+2];

		_items[1*4+3] = lpValue[3*4+1];
		_items[3*4+1] = lpValue[1*4+3];

		_items[2*4+3] = lpValue[3*4+2];
		_items[3*4+2] = lpValue[2*4+3];
	}


	void Scale( const Vector3<Type>& vector )
	{
		_items[0*4+0] *= vector.x;
		_items[1*4+0] *= vector.x;
		_items[2*4+0] *= vector.x;
		_items[3*4+0] *= vector.x;

		_items[0*4+1] *= vector.y;
		_items[1*4+1] *= vector.y;
		_items[2*4+1] *= vector.y;
		_items[3*4+1] *= vector.y;

		_items[0*4+2] *= vector.z;
		_items[1*4+2] *= vector.z;
		_items[2*4+2] *= vector.z;
		_items[3*4+2] *= vector.z;
	}

	void Translate( const Vector3<Type>& vector )
	{
		_items[3*4+0] += vector.x;
		_items[3*4+1] += vector.y;
		_items[3*4+2] += vector.z;
	}

	Type* GetItems()
	{
		return _items;
	}

	const Type* GetItems() const
	{
		return _items;
	}

	void MatrixToSRT( Vector3<Type>& Scale, 
		Quaternion<Type>& Rotate,
		Vector3<Type>& Translate  )
	{
		Type				sx, sy, sz, value;
		Matrix4x4<Type>		mRot;

		// get scale
		Scale.x = sqrt(this->_items[0] * this->_items[0] + this->_items[1] * this->_items[1] + this->_items[2] * this->_items[2]);
		Scale.y = sqrt(this->_items[4] * this->_items[4] + this->_items[5] * this->_items[5] + this->_items[6] * this->_items[6]);
		Scale.z = sqrt(this->_items[8] * this->_items[8] + this->_items[9] * this->_items[9] + this->_items[10] * this->_items[10]);

		// get rotate
		sx = 1.0f / Scale.x;
		sy = 1.0f / Scale.y;
		sz = 1.0f / Scale.z;

		mRot.GetItems()[0] = this->_items[0] * sx;
		mRot.GetItems()[1] = this->_items[1] * sx;
		mRot.GetItems()[2] = this->_items[2] * sx;

		mRot.GetItems()[4] = this->_items[4] * sy;
		mRot.GetItems()[5] = this->_items[5] * sy;
		mRot.GetItems()[6] = this->_items[6] * sy;

		mRot.GetItems()[8] = this->_items[8] * sz;
		mRot.GetItems()[9] = this->_items[9] * sz;
		mRot.GetItems()[10] = this->_items[10] * sz;

		value = mRot.GetItems()[0] + mRot.GetItems()[5] + mRot.GetItems()[10] + 1.0f;

		if( value > 0.0001 )
		{
			Rotate.w = sqrt(value) * 0.5f;

			value = 1.0f / (Rotate.w * 4.0f);

			Rotate.x = (mRot.GetItems()[6] - mRot.GetItems()[9]) * value;
			Rotate.y = (mRot.GetItems()[8] - mRot.GetItems()[2]) * value;
			Rotate.z = (mRot.GetItems()[1] - mRot.GetItems()[4]) * value;
		}
		else
		{
			if((mRot.GetItems()[0] >= mRot.GetItems()[5]) && (mRot.GetItems()[0] >= mRot.GetItems()[10]))      // Qx is max
			{
				value = sqrt(mRot.GetItems()[0] - mRot.GetItems()[5] - mRot.GetItems()[10] + 1.0f) * 2.0f;

				Rotate.x = value * 0.25f;

				value = 1.0f / value;

				Rotate.y = (mRot.GetItems()[1] + mRot.GetItems()[4]) * value;
				Rotate.z = (mRot.GetItems()[2] + mRot.GetItems()[8]) * value;
				Rotate.w = (mRot.GetItems()[6] - mRot.GetItems()[9]) * value;
			}
			else if((mRot.GetItems()[5] >= mRot.GetItems()[0]) && (mRot.GetItems()[5] >= mRot.GetItems()[10])) // Qy is max
			{
				value = sqrt(mRot.GetItems()[5] - mRot.GetItems()[0] - mRot.GetItems()[10] + 1.0f) * 2.0f;

				Rotate.y = value * 0.25f;

				value = 1.0f / value;

				Rotate.x = (mRot.GetItems()[1] + mRot.GetItems()[4]) * value;
				Rotate.z = (mRot.GetItems()[6] + mRot.GetItems()[9]) * value;
				Rotate.w = (mRot.GetItems()[8] - mRot.GetItems()[2]) * value;
			}
			else                                                    // Qz is max
			{
				value = sqrt(mRot.GetItems()[10] - mRot.GetItems()[0] - mRot.GetItems()[5] + 1.0f) * 2.0f;

				Rotate.z = value * 0.25f;

				value = 1.0f / value;

				Rotate.x = (mRot.GetItems()[2] + mRot.GetItems()[8]) * value;
				Rotate.y = (mRot.GetItems()[6] + mRot.GetItems()[9]) * value;
				Rotate.w = (mRot.GetItems()[1] - mRot.GetItems()[4]) * value;
			}
		}

		// get translate
		Translate.x = this->_items[12];
		Translate.y = this->_items[13];
		Translate.z = this->_items[14];
	}

	Matrix4x4<Type>& operator = ( const Matrix4x4<Type>& rhs )
	{
		const Type* pRHSItems = rhs.GetItems();

		memcpy( (void*)_items, (const void*)pRHSItems, sizeof(_items) );

		return *this;
	}

	Matrix4x4<Type>& operator *= ( const Matrix4x4<Type>& rhs )
	{
		Matrix4x4<Type> temp;
		Type* pTempItems = temp.GetItems();

		const Type* pRHSItems = rhs.GetItems();

		int i;
		for ( i = 0; i < 4; i++)
		{
			pTempItems[i * 4 + 0] = _items[i * 4 + 0] * pRHSItems[ 0 * 4 + 0] +
				_items[i * 4 + 1] * pRHSItems[ 1 * 4 + 0] +
				_items[i * 4 + 2] * pRHSItems[ 2 * 4 + 0] +
				_items[i * 4 + 3] * pRHSItems[ 3 * 4 + 0];					

			pTempItems[i * 4 + 1] = _items[i * 4 + 0] * pRHSItems[ 0 * 4 + 1] +
				_items[i * 4 + 1] * pRHSItems[ 1 * 4 + 1] +
				_items[i * 4 + 2] * pRHSItems[ 2 * 4 + 1] +
				_items[i * 4 + 3] * pRHSItems[ 3 * 4 + 1];

			pTempItems[i * 4 + 2] = _items[i * 4 + 0] * pRHSItems[ 0 * 4 + 2] +
				_items[i * 4 + 1] * pRHSItems[ 1 * 4 + 2] +
				_items[i * 4 + 2] * pRHSItems[ 2 * 4 + 2] +
				_items[i * 4 + 3] * pRHSItems[ 3 * 4 + 2];

			pTempItems[i * 4 + 3] = _items[i * 4 + 0] * pRHSItems[ 0 * 4 + 3] +
				_items[i * 4 + 1] * pRHSItems[ 1 * 4 + 3] +
				_items[i * 4 + 2] * pRHSItems[ 2 * 4 + 3] +
				_items[i * 4 + 3] * pRHSItems[ 3 * 4 + 3];
		} // End for    
			
		memcpy( (void*)_items, (const void*)pTempItems, sizeof(_items) );

		return *this;
	}
	
	static Matrix4x4<Type>& GetIdentity()
	{
		static Matrix4x4<Type> identity( 1, 0, 0, 0,
										0, 1, 0, 0,
										0, 0, 1, 0,
										0, 0, 0, 1 );

		return identity;
	}

private:
	Type _items[16];
};
}

