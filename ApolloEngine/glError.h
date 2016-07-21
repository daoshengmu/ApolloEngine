#pragma  once

#include <stdlib.h>
#include <assert.h>
#include "GL/glew.h"

/**
*
* @file     glError.h
* @author   Daosheng Mu
* @version  1.0
*
* @section  LICENSE
*
* (C) All rights reserved.
*
* @section	Description
*
* Check OpenGL error
*
*/

namespace Apollo
{
	static bool CheckForErrors()
	{
#ifdef _DEBUG
		static bool checkForErrors = true;
#else
		static bool checkForErrors = false;
#endif
		//
		if( !checkForErrors )
		{
			return false;
		}

		//
		const char * errorString = NULL;
		bool retVal = false;

		switch( glGetError() )
		{
		case GL_NO_ERROR:
			retVal = true;
			break;

		case GL_INVALID_ENUM:
			errorString = "GL_INVALID_ENUM";
			break;

		case GL_INVALID_VALUE:
			errorString = "GL_INVALID_VALUE";
			break;

		case GL_INVALID_OPERATION:
			errorString = "GL_INVALID_OPERATION";
			break;

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;

			// OpenGLES Specific Errors
#ifdef ATHENA_OPENGLES
		case GL_STACK_OVERFLOW:
			errorString = "GL_STACK_OVERFLOW";
			break;

		case GL_STACK_UNDERFLOW:
			errorString = "GL_STACK_UNDERFLOW";
			break;
#endif

		case GL_OUT_OF_MEMORY:
			errorString = "GL_OUT_OF_MEMORY";
			break;

		default:
			errorString = "UNKNOWN";
			break;
		}

		//
		if( !retVal )
		{
			printf( "%d %s\n", glGetError(), errorString );
			assert( retVal );
		}

		//
		return retVal;
	}

	//
	//
	static void ClearErrors()
	{
		while( glGetError() != GL_NO_ERROR );
	}
}