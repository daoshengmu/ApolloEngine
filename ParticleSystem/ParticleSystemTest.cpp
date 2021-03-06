// ParticleSystem.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ParticleSystemTest.h"
#include "Renderer.h"
#include "LightManager.h"
#include "Nurbs.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
const UINT windowWidth = 1024;
const UINT windowHeight = 768;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void Update();
void __cdecl WinOutput( char *szString, ... );

using namespace Apollo;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PARTICLESYSTEM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PARTICLESYSTEM));

	LightManager::Instance().SetAmbientColor( Vector4f( 0.2f, 0.2f, 0.2f, 1.0f ) );
	Vector3f dir( 0, 1, 0 );		
	LightManager::Instance().SetDirection( dir );
	LightManager::Instance().SetDirectionalColor( Vector4f( 1, 1, 1, 1 ) );

	Renderer &renderer = Renderer::Instance();	
	renderer.SetClearColor( Vector4f( 0,0,0,1) );

	Camera *pCamera = renderer.GetCamera();
	TransformNode* node = pCamera->GetTransformNode();
	pCamera->SetViewPort( (float)windowWidth, (float)windowHeight );
	pCamera->SetCameraType(Camera::CT_ORTHOGONAL);	
	node->SetOrigin( Vector3f( 0, -5, 0 ) );

	// Create squareA
	Square* squareA = renderer.CreateSquare();
	Material *pMaterial = squareA->GetSurface()->GetMaterial();
	pMaterial->SetMaterialColor( Vector4f( 1, 0, 0, 1) );
	node = squareA->GetTransformNode();
	node->SetOrigin( Vector3f(-150, 0, 0) );
	node->SetScale( Vector3f( 50, 50, 50 ) );
	renderer.AddRenderItem( squareA );

	// Create squareB
	Square* squareB = renderer.CreateSquare();
	pMaterial = squareB->GetSurface()->GetMaterial();
	pMaterial->SetMaterialColor( Vector4f( 1, 0, 0, 1) );
	node = squareB->GetTransformNode();
	node->SetOrigin( Vector3f(150, 0, 0) );
	node->SetScale( Vector3f( 50, 50, 50 ) );
	renderer.AddRenderItem( squareB );

	// Create particleA
	ParticleSystem* particleSystemA = renderer.CreateParticleSystem();
	pMaterial = particleSystemA->GetSurface()->GetMaterial();
	particleSystemA->SetMaxNumParticles( 100 );
	particleSystemA->SetParticleSpeed( 1.0f );
	Vector2f particleDir( 1, 1 );
	particleDir.Normalize();
	particleSystemA->SetParticleDirection( particleDir );
	pMaterial->SetMaterialColor( Vector4f( 0, 0, 1, 1 ) );
	node = particleSystemA->GetTransformNode();
	node->SetOrigin( Vector3f(30,0,0) );		
	renderer.AddRenderItem( particleSystemA );

	// Create squareB
	ParticleSystem* particleSystemB = renderer.CreateParticleSystem();
	pMaterial = particleSystemB->GetSurface()->GetMaterial();
	particleSystemB->SetMaxNumParticles( 100 );
	particleSystemB->SetParticleSpeed( 1.0f );
	particleDir.x = -1.0f;
	particleDir.y = 1.0f;
	particleDir.Normalize();
	particleSystemB->SetParticleDirection( particleDir );
	pMaterial->SetMaterialColor( Vector4f( 0, 0, 1, 1 ) );
	node = particleSystemB->GetTransformNode();
	node->SetOrigin( Vector3f(-30,0,0) );
	renderer.AddRenderItem( particleSystemB );

	/*
	// Try the Nurbs formula
	Nurbs *nurbCurve = new Nurbs();
	std::vector<int> knot;

	float b[31];  // allows for up to 10  control vertices
	memset( b, 0, sizeof( b ) );
	b[1]=0;
	b[2]=0;
	b[3]=0.1;
	b[4]=0.1;
	b[5]=0.2;
	b[6]=0.1;
	b[7]=0.25;
	b[8]=0;
	b[9]=0.1;
	b[10]=0.4;
	b[11]=0.2;
	b[12]=0.1;
	b[13]=0.5;
	b[14]=0;
	b[15]=0.1;
	
	int npts,k,p1;
	npts = 5;
	k = 3;     //third order, change for other orders 
	p1 = 11;   // eleven points on curve
	float p[103];
	memset( p, 0, sizeof( p ) );
	int i;
	float h[11];
	
	h[0] = 0.0;
	for (i=1; i <= npts; i++){
		h[i] = 1.0;
	}

	//  vary the homogeneous weighting factor 0, 0.25, 1.0, 5.0 

	h[3] = 1;

	nurbCurve->RationalBSplineCurve( npts, k, p1, b, h, p );

	WinOutput("\nPolygon points\n");

	for (i = 1; i <= 3*npts; i=i+3){
		WinOutput(" %f %f %f \n",b[i],b[i+1],b[i+2]);
	}

	WinOutput("\nHomogeneous weighting vector is \n");
	for (i = 1; i <= npts; i++){
		WinOutput(" %f ", h[i]);
	}
	WinOutput("\n");


	WinOutput("\nCurve points\n");

	for (i = 1; i <= 3*p1; i=i+3){
		WinOutput(" %f %f %f \n",p[i],p[i+1],p[i+2]);
	}

	// End of Nurbs 
	*/


	memset(&msg,0,sizeof(msg));

	// Main message loop:
	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			Update();
		}
	}

	renderer.Terminate();

	return (int) msg.wParam;
}

void Update()
{
	Renderer &renderer = Renderer::Instance();	

	renderer.Update();
}

//------------------------------------------------------------------------
void __cdecl WinOutput( char *szString, ... )
{
	char szStr[1024];

	va_list params;
	va_start( params, szString );
	
	vsprintf_s( szStr, szString, params );
	
	OutputDebugStringA( szStr );
	OutputDebugStringA( "\n" );
}; // End of WinOutput

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PARTICLESYSTEM));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PARTICLESYSTEM);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   Renderer &renderer = Renderer::Instance();

   renderer.Initialize( hWnd, windowWidth, windowHeight );

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
