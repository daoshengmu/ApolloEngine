// Simple3DTransfrom.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Renderer.h"
#include "Simple3DTransfrom.h"
#include "LightManager.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

using namespace Apollo;
const UINT windowWidth = 1024;
const UINT windowHeight = 768;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void Update();

Cube *cubeA = NULL;
Cube *cubeB = NULL;

struct TransformCubeB
{
	//Matrix4x4f _matrixA;
	Vector3f _axis;
	float    _angle;
	Vector3f _vectorBA;
};

TransformCubeB transformCubeB;

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
	LoadString(hInstance, IDC_SIMPLE3DTRANSFROM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	Renderer &renderer = Renderer::Instance();	
	renderer.SetClearColor( Vector4f( 0, 1, 0, 1 ) );

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLE3DTRANSFROM));

	LightManager::Instance().SetAmbientColor( Vector4f( 0.2f, 0.2f, 0.2f, 1 ) );
	Vector3f dir( 0, -1, 15 );	
	dir.Normalize();
	LightManager::Instance().SetDirection( dir );
	LightManager::Instance().SetDirectionalColor( Vector4f( 1, 1, 0, 1 ) );

	TransformNode* node = NULL;
	Camera *camera = renderer.GetCamera();
	camera->SetViewPort( (float)windowWidth, (float)windowHeight );
	node = camera->GetTransformNode();
 	node->SetOrigin( Vector3f( 0, -20, 5 ) );
   	node->SetPitchDeltaAngle( -45.0f );	
		
	cubeA = renderer.CreateCube();
	renderer.AddRenderItem( cubeA );

	cubeB = renderer.CreateCube();
	renderer.AddRenderItem( cubeB );

	node = cubeA->GetTransformNode();

	node->SetScale( Vector3f( 2, 2, 2 ) ); 
	node->SetOrigin( Vector3f( 0,0,0 ) );
//	transformCubeB._matrixA = *node->GetWorldMatrix();

 	node = cubeB->GetTransformNode();
 
 	node->SetScale( Vector3f(1,1,1) );
 	node->SetOrigin( Vector3f( 0, 5, 5 ) );

	TransformNode *nodeA = cubeA->GetTransformNode();
	TransformNode *nodeB = cubeB->GetTransformNode();

	const Vector3f *nodeBPos = nodeB->GetOrigin();
	const Vector3f *nodeAPos = nodeA->GetOrigin();

	Vector3f distance = *nodeB->GetOrigin() - *nodeA->GetOrigin();
	float length = distance.Length();	

	transformCubeB._vectorBA = distance;

	Vector3f axis;

	nodeA->GetRightVector( axis );
	transformCubeB._axis = axis;
	transformCubeB._angle = 0;	
	
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
	
	TransformNode *nodeA = cubeA->GetTransformNode();
	TransformNode *nodeB = cubeB->GetTransformNode();
	
 	Quaternionf transformQuaterrnion;
 
 	transformCubeB._angle += 1.0f;
 	transformQuaterrnion.fromAngleAxis( transformCubeB._angle, transformCubeB._axis );
 	Vector3f finalPosition = transformQuaterrnion.TransformVector3D( transformCubeB._vectorBA );

	nodeB->SetOrigin( finalPosition );

	nodeA->SetYawDeltaAngle( 5.0f );
	
	renderer.Update();
}

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPLE3DTRANSFROM));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SIMPLE3DTRANSFROM);
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
      CW_USEDEFAULT, 0, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

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
