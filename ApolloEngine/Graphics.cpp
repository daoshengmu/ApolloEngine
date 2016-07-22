
#include "stdafx.h"
#include "Graphics.h"
#include "Surface.h"
#include "glError.h"
#include <assert.h>
#include "LightManager.h"
#include "ConstantTable.h"
#include <GL/wglext.h>

namespace Apollo
{

typedef struct
{
	GLuint reg;
	GLint numComp;
	uint dataFormat;
	GLboolean normalized;
	uint compSize;
	uint totalStride;
} VertexElement;

VertexElement ElementDecl_POS_COLOR_NORMAL[] = 
{ 
	{ 0, 3, GL_FLOAT, GL_FALSE, 12, 48 },
	{ 1, 4, GL_FLOAT, GL_FALSE, 16, 48 }, 
	{ 2, 2, GL_FLOAT, GL_FALSE, 8, 48 },
	{ 3, 3, GL_FLOAT, GL_FALSE, 12, 48 }
};

typedef struct
{
	VertexElement *element;
	size_t size;
} VertexDecl;

#define ADD_VERTEX_DECL( type ) { type, sizeof( type ) / sizeof( VertexElement ) }
VertexDecl gVertexDeclResource[] = 
{
	ADD_VERTEX_DECL( ElementDecl_POS_COLOR_NORMAL )
};

std::map< const char*, int> ConstantTable::_value;

bool Graphics::Initialize( HWND hWnd, UINT width, UINT height, bool bFullScreen )
{
	PIXELFORMATDESCRIPTOR pfd;

	memset( &pfd, 0, sizeof( PIXELFORMATDESCRIPTOR ) );

	pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;

	_wndHandle = hWnd;
	_glDev = GetDC( hWnd );

	GLuint iPixelFormat = ChoosePixelFormat( _glDev, &pfd );

	if ( iPixelFormat != 0 )
	{
		PIXELFORMATDESCRIPTOR bestMatch_pfd;
		DescribePixelFormat( _glDev, iPixelFormat, sizeof(pfd), &bestMatch_pfd );

		if ( bestMatch_pfd.cDepthBits < pfd.cDepthBits )
		{
			return false;
		}

		if ( SetPixelFormat( _glDev, iPixelFormat, &pfd ) == false )
		{
			return false;
		}
	}
	else
	{ 
		return false;
	}
  
  _glhRC = wglCreateContext(_glDev);

	wglMakeCurrent( _glDev, _glhRC );

	GLenum err = glewInit();

	if ( err != GLEW_OK )
	{
		return false;
	}

	if ( bFullScreen ) // This is just an experimental work, you need to have some modifications. By Ellison.
	{
		//
		// Enumerate Device modes...
		//
		int nMode = 0;
		DEVMODE devMode;
		bool bDesiredDevModeFound = false;

		while( EnumDisplaySettings( NULL, nMode++, &devMode ) )
		{
			// Does this device mode support a 640 x 480 setting?
			if( devMode.dmPelsWidth != 640 || devMode.dmPelsHeight != 480)
				continue;

			// Does this device mode support 32-bit color?
			if( devMode.dmBitsPerPel != 32 )
				continue;

			// Does this device mode support a refresh rate of 75 MHz?
			if( devMode.dmDisplayFrequency != 75 )
				continue;

			// We found a match, but can it be set without rebooting?
			if( ChangeDisplaySettings( &devMode, CDS_TEST ) == DISP_CHANGE_SUCCESSFUL )
			{
				bDesiredDevModeFound = true;
				break;
			}
		}

		if( bDesiredDevModeFound == false )
		{
			// TO DO: Handle lack of support for desired mode...
			return false;
		}

		if( ChangeDisplaySettings( &devMode, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			// TO DO: Respond to failure of ChangeDisplaySettings
			return false;
		}
	} // End of if-bFullScreen

  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB 
    = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
  if (wglCreateContextAttribsARB)
  {
    GLint attribs[] =
    {
      // Here we ask for OpenGL 4.5
      WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
      WGL_CONTEXT_MINOR_VERSION_ARB, 5,
      0
    };
    _glhRC = wglCreateContextAttribsARB(_glDev, 0, attribs);

    if (_glhRC)
    {
      wglMakeCurrent(_glDev, _glhRC);
    }
  }

  printf("OpenGL version supported by this platform (%s): \n",
    glGetString(GL_VERSION));

	SetViewPort( 0, 0, width, height );
  	glEnable( GL_CULL_FACE );
  	glFrontFace( GL_CCW );
  	glCullFace( GL_BACK );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		
	glEnable(GL_BLEND);
	//glDisable( GL_CULL_FACE );
	
	return true; 

}

void Graphics::ClearColor( const Vector4f &color )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	glClearColor( color.x, color.y, color.z, color.w );
	glClearDepth( 1.0f );
	glClearStencil( 0 );
	CheckForErrors();
		
// 	GLUnurbs *theNurb=gluNewNurbsRenderer();
// 	gluNurbsProperty(theNurb,GLU_SAMPLING_TOLERANCE,10.0);
// 	gluNurbsProperty(theNurb,GLU_DISPLAY_MODE,GLU_FILL);
// 	GLfloat ctrlpoints[9][3] = {{ 0.000000, 1.000000, 0.000000  },{ 1.000000, 1.000000, 2.000000 },{2.500000, 1.000000 , 0.000000},{4.000000, 1.000000, 2.000000 },
// 	{5.000000, 1.000000, 0.000000 }};
// 
// 	GLfloat knots[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
// 	gluBeginCurve(theNurb);
// 	gluNurbsCurve(theNurb,12,knots,3,&ctrlpoints[0][0],3,GL_MAP1_VERTEX_3);
// 	gluEndCurve(theNurb);	 
}

void Graphics::Terminate()
{
	
}

void Graphics::EndFrame()
{	
	SwapBuffers( _glDev );
	CheckForErrors();
}

void Graphics::CreateBuffer( const float* vertexData, const uint16* indexData, Surface* pSurface )
{
	VertexBuffer vertexBuffer;
	
	uint numVertices = pSurface->GetNumVertices();
	uint vertexSize = pSurface->GetVertexSize();
	uint numIndices = pSurface->GetNumIndices();

	bool check = CheckForErrors();

	glGenBuffers( 1, &vertexBuffer );
	 check = CheckForErrors();
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
	 check = CheckForErrors();
	glBufferData( GL_ARRAY_BUFFER, numVertices * vertexSize, vertexData, GL_DYNAMIC_DRAW );
	 check = CheckForErrors();
	
	IndexBuffer indexBuffer;
	
	glGenBuffers( 1, &indexBuffer );
	 check = CheckForErrors();
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	 check = CheckForErrors();
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof( uint16 ), indexData, GL_DYNAMIC_DRAW );
	 check = CheckForErrors();
	
	pSurface->SetVertexBuffer( vertexBuffer );
	pSurface->SetIndexBuffer( indexBuffer );

}

Program Graphics::CreateProgram( const std::string& vertexShaderStr, const std::string& fragShaderStr )
{
	Program program;
	Shader vertexShader;
	Shader fragmentShader;	
	const char* shaderData;

	shaderData = vertexShaderStr.c_str();
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
    CheckForErrors();
	glShaderSource( vertexShader, 1, &shaderData, NULL );
	CheckForErrors();
	glCompileShader( vertexShader );
	CheckForErrors();
	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	CheckForErrors();
	shaderData = fragShaderStr.c_str();
	glShaderSource( fragmentShader, 1, &shaderData, NULL );
	CheckForErrors();
	glCompileShader( fragmentShader );
	CheckForErrors();
	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		GLchar infoLog[256];
		glGetShaderInfoLog( vertexShader, maxLength, &maxLength, infoLog );
		//We don't need the shader anymore.
		glDeleteShader(vertexShader);
		//Use the infoLog as you see fit.
		assert( 0 && "ContextOGL:: Create vertex shader error" );
		return NULL;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		char infoLog[256];
		glGetShaderInfoLog( fragmentShader, maxLength, &maxLength, infoLog );

		//We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		//Use the infoLog as you see fit.
		assert( 0 && "ContextOGL:: Create fragment shader error" );
		return NULL;
	}

	program = glCreateProgram();
	glAttachShader( program, vertexShader );
	glAttachShader( program, fragmentShader );
	const GLuint vertexLoc = 0;
	const GLuint colorLoc = 1;
	const GLuint texLoc = 2;
	const GLuint normalLoc = 3;
	// Init attributes BEFORE linking
	glBindAttribLocation(program, vertexLoc, "g_vPositionOS");
	glBindAttribLocation(program, colorLoc, "g_vColorOS");
	glBindAttribLocation(program, texLoc, "g_vTextCoordOS");
	glBindAttribLocation(program, normalLoc, "g_vNormalOS");
	glLinkProgram( program );

	GLuint pos = glGetAttribLocation( program, "g_vNormalOS" );
	
	int i = glGetUniformLocation( program, g_worldViewProjMatrix );
	 ConstantTable::InsertToConstantMap( g_worldViewProjMatrix, i );
	 i = glGetUniformLocation( program, g_worldMatrix );
	 ConstantTable::InsertToConstantMap( g_worldMatrix, i );
	 i = glGetUniformLocation( program, g_worldViewMatrix );
	 ConstantTable::InsertToConstantMap( g_worldViewMatrix, i );
	 i = glGetUniformLocation( program, g_eyePosition );
	 ConstantTable::InsertToConstantMap( g_eyePosition, i );
	 i = glGetUniformLocation( program, g_sunlightDir );
	 ConstantTable::InsertToConstantMap( g_sunlightDir, i );
	 i = glGetUniformLocation( program, g_sunlightColor );
	 ConstantTable::InsertToConstantMap( g_sunlightColor, i );
	 i = glGetUniformLocation( program, g_sunlightAmbient );	
	 ConstantTable::InsertToConstantMap( g_sunlightAmbient, i );
	 i = glGetUniformLocation( program, g_materialColor );
	 ConstantTable::InsertToConstantMap( g_materialColor, i );

	// Check for link success
	GLint maxLength = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &maxLength);
	if (!maxLength)
	{
		GLchar infoLog[ 256 ];

		glGetProgramInfoLog( program, maxLength, &maxLength, infoLog );
		glDeleteShader( vertexShader );
		glDeleteShader( fragmentShader );
		glDeleteProgram( program );
		return NULL;
	}
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );
	
	return program;

}

void Graphics::SetProgramConstantsFromMatrix( int firstRegister, const Matrix4x4f &matrix )
{ 
	glUniformMatrix4fv( firstRegister, 1, GL_FALSE, matrix.GetItems() );
	bool check = CheckForErrors();
}

void Graphics::SetProgramConstantsFromVector( int firstRegister, const Vector4f &vector )
{
	glUniform4fv( firstRegister, 1, (GLfloat *)(&vector) );
	bool check = CheckForErrors();
}

void Graphics::SetProgram( Program program )
{
	glUseProgram( program );
	bool check = CheckForErrors();
}

void Graphics::SetVertexDeclaration( EVertexDecl vtxDclType )
{
	int offset = 0;
	VertexDecl decl(gVertexDeclResource[ vtxDclType ]);

	int size = static_cast<int>(decl.size);
	VertexElement *element = decl.element;

	for ( int i = 0; i < size; ++i )
	{ 
		glVertexAttribPointer( element[i].reg, element[i].numComp, element[i].dataFormat, element[i].normalized, element[i].totalStride, (GLvoid *)offset );
		glEnableVertexAttribArray( element[i].reg );
		bool check = CheckForErrors();
		offset += element[i].compSize;
	}
}

void Graphics::SetVertexBufferAt( int index, VertexBuffer buffer )
{
	glBindBuffer( GL_ARRAY_BUFFER, buffer ); 
	bool check = CheckForErrors();
}

void Graphics::_DrawTriangles( IndexBuffer indexBuffer, uint numIndices )
{ 
	// Set index buffer 
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
	bool check = CheckForErrors();
	
	// Draw triangles
	glDrawElements( GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0 ); 
	 check = CheckForErrors();
}

void Graphics::Draw( const Surface *surf )
{
	const Material *pMaterial = surf->GetMaterial();
	const Vector4f *pMaterialColor = pMaterial->GetMaterialColor();
	const Matrix4x4f *pWorldMtx = surf->GetWorldMatrix();
	//Matrix4x4f transposedMatrix;

	this->SetProgram( pMaterial->GetProgram() );
		
	this->SetProgramConstantsFromVector( ConstantTable::FindConstantIndex( g_eyePosition), Vector4f( _eyePosition.x, _eyePosition.y, _eyePosition.z, 1.0f ) );
	this->SetProgramConstantsFromVector( ConstantTable::FindConstantIndex( g_materialColor ), Vector4f( pMaterialColor->x, pMaterialColor->y, pMaterialColor->z, pMaterialColor->w ) );
	// Set light parameters to shader
	const Vector4f *color = LightManager::Instance().GetAmbientColor();
	this->SetProgramConstantsFromVector( ConstantTable::FindConstantIndex( g_sunlightAmbient ), *color );
	color = LightManager::Instance().GetDirectionalColor();
	this->SetProgramConstantsFromVector( ConstantTable::FindConstantIndex( g_sunlightColor ), *color );
	const Vector3f *dir = LightManager::Instance().GetDirection();
	Vector4f lightDir( -dir->x, -dir->y , -dir->z, 1 );
	this->SetProgramConstantsFromVector( ConstantTable::FindConstantIndex( g_sunlightDir ), lightDir );
	// End of setting light

	if ( pWorldMtx ) 
	{		
		_worldViewProjMatrix = *pWorldMtx;
		_worldViewProjMatrix *= _viewProjMatrix;
	
		this->SetProgramConstantsFromMatrix( ConstantTable::FindConstantIndex( g_worldViewProjMatrix ), _worldViewProjMatrix ); // mvp mtx 5

		_worldViewMatrix = *pWorldMtx; 
		_worldViewMatrix *= _viewMatrix; // world-view mtx 		
		
	}
	else
	{
		this->SetProgramConstantsFromMatrix( ConstantTable::FindConstantIndex( g_worldViewProjMatrix ), _viewProjMatrix ); // mvp mtx 5
	}

	if ( pWorldMtx )
	{ 				
		this->SetProgramConstantsFromMatrix( ConstantTable::FindConstantIndex( g_worldMatrix ), *pWorldMtx );		
	} 
	else
	{				
		this->SetProgramConstantsFromMatrix( ConstantTable::FindConstantIndex( g_worldMatrix ), Matrix4x4f::GetIdentity() );		
	}

	this->SetVertexBufferAt( 0, surf->GetVertexBuffer() );
	this->SetVertexDeclaration( pMaterial->GetVertexDeclaration() );
	this->_DrawTriangles( surf->GetIndexBuffer(), surf->GetNumIndices() );
}

void Graphics::SetCamera( Camera *pCamera )
{
	_viewMatrix = *pCamera->GetViewMatrix();
	
	const Matrix4x4f *pProj = pCamera->GetProjectionMatrix();
	_viewProjMatrix = _viewMatrix;
	_viewProjMatrix *= *pProj;

	const Vector3f *eyePosition = pCamera->GetTransformNode()->GetOrigin();
	_eyePosition = *eyePosition;	
}

void Graphics::SetViewPort( uint x, uint y, uint width, uint height )
{
	glViewport( (GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height );
	CheckForErrors();
}

void Graphics::_DrawCurve()
{
	int i ;
	GLfloat ctrlpoints[4][3] = {
		{ -4, 0, -4.0}, { -2, 0, 4.0}, 
		{2, 0, -4.0}, {4, 0, 4.0}};
		GLUnurbs *theNurb=gluNewNurbsRenderer();
		GLfloat knots[8] = {0,0,0,0,1,1,1,1};
		glColor3f(1.0, 1.0, 1.0);
		gluBeginCurve(theNurb);
		gluNurbsCurve(theNurb,8,knots,3,&ctrlpoints[0][0],4,GL_MAP1_VERTEX_3);
		gluEndCurve(theNurb);
		// 		glMatrixMode(GL_PROJECTION);
		// 		glLoadIdentity();
		// 		int w = 1024;
		// 		int h = 768;
		// 		if (w <= h)
		// 			glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
		// 			5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
		// 		else
		// 			glOrtho(-5.0*(GLfloat)w/(GLfloat)h, 
		// 			5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
		// 		glMatrixMode(GL_MODELVIEW);
		// 		glLoadIdentity();
		// 		int i ;
		// 		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
		// 		glEnable(GL_MAP1_VERTEX_3);
		// 		glColor3f(1.0, 1.0, 1.0);
		// 		glBegin(GL_LINE_STRIP);
		// 		for (i = 0; i <= 30; i++) 
		// 			glEvalCoord1f((GLfloat) i/30.0);
		// 		glEnd();
		/* The following code displays the control points as dots. */
		glPointSize(5.0);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		for (i = 0; i < 4; i++) 
			glVertex3fv(&ctrlpoints[i][0]);
		glEnd();

}

}