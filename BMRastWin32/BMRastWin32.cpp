// BMRastWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "BMRastWin32.h"
#include <iostream>

#include "../BMRast/Surface.h"

CSurface* gSurface;
CSurface* gSurfaceMandelbort;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void UFillSurface()
{
	static unsigned gRotation = 0;

	gSurface->Fill(RGB(0,0,0));
	//gSurface->FillMandelbortFractal();
	gSurface->FillRect(0,0, 32, 32, RGB(255, 0,0));
	gSurface->FillRect(300, 300, 32, 32, RGB(255, 0,0));
	

	
	gSurface->DrawSurfaceRotatedCenter(Int2(64,64), gSurfaceMandelbort, gRotation);
	gSurface->DrawSurfaceRotated(Int2(200, 200), gSurfaceMandelbort, gRotation, Int2(0,0));

	gSurface->SetPixel<true>( 64, 64,  4, RGB(255, 255, 0));
	gSurface->SetPixel<true>( 200, 200,  4, RGB(255, 255, 0));

	gSurface->DrawLineAA(0,0, 200, 200, RGB(0, 0, 255));

	gSurface->DrawLineAA( 200, 200, 200 + sin((float)gRotation) * 100, 200 + cos((float)gRotation) * 100, RGB(0, 0, 255));
	

	//gRotation += 1;
	return;

	for(unsigned i = 0; i < 8; i++)
	{
		gSurface->FillRect(rand() % 600, rand() % 600,  32, 32, RGB(255, 0, 0));
	}
	for(unsigned i = 0; i < 8; i++)
	{
		int x = rand() % 600;
		int y = rand() % 600;
		gSurface->DrawSurfaceRotatedCenter(Int2(x, y), gSurfaceMandelbort, rand() % 360);
		gSurface->SetPixel<true>(x, y, 4, RGB(255, 255, 255));
	}


	for(unsigned i = 0; i < 3; i++)
	{
		gSurface->DrawVerticalLine(0, 1000, rand() % 600, rand() % 8, RGB(255, 0,0));
		gSurface->DrawHorizontalLine(0, 1000, rand() % 600, rand() % 8, RGB(255, 0, 0));
	}
	for(unsigned i = 0; i < 6; i++)
	{
		gSurface->DrawLine(rand() % 1000, rand() % 1000, rand() % 1000, rand() % 1000, rand() % 16, RGB(0, 255, 0));
	}
}
// int APIENTRY _tWinMain(HINSTANCE hInstance,
//                      HINSTANCE hPrevInstance,
//                      LPTSTR    lpCmdLine,
//                      int       nCmdShow)
int main(int argc, char** argv)
{
 	// TODO: Place code here.
	int n = int(-1);
	unsigned test = *((unsigned*)&n);

	unsigned char ssss = (unsigned char)(char)(char(-1));
	unsigned ss1 = unsigned(1) << 31;
	unsigned asd = (unsigned)(int(-777777));
	
	printf("%x  %x %x", asd, ss1, test);

	std::cout << std::hex << ssss;


	gSurfaceMandelbort = CSurface::Create(64, 64);
	gSurfaceMandelbort->Fill(RGB(0,0,0));
	gSurfaceMandelbort->FillMandelbortFractal();
	
	gSurface = CSurface::Create(800, 800);
	gSurface->FillRect(0,0, 600, 600, RGB(255, 255,0));
	UFillSurface();

	srand(GetTickCount());



	MSG msg;
	HACCEL hAccelTable;

	HINSTANCE hInstance = GetModuleHandle(NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BMRASTWIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, SW_NORMAL))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BMRASTWIN32));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UFillSurface();
		InvalidateRect(msg.hwnd, NULL, false);
		Sleep(100);
	}

	return (int) msg.wParam;
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BMRASTWIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BMRASTWIN32);
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
	case WM_CREATE:
		{
			HDC hdc = GetDC(hWnd);
			ReleaseDC(hWnd, hdc);

		};
		break;

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
		{
			hdc = BeginPaint(hWnd, &ps);

			HBITMAP bmp = CreateBitmap(gSurface->Width(), gSurface->Height(), 1, 32, gSurface->GetPixels());
			HBRUSH br = CreatePatternBrush(bmp);
			RECT rect = {0,0, gSurface->Width(), gSurface->Height() };
			FillRect(hdc, &rect, br);
			DeleteObject(br);
			DeleteObject(bmp);

			if(0)
			{

				// TODO: Add any drawing code here...
				for(unsigned y = 0; y < gSurface->Height(); y++)
				{
					for(unsigned x = 0; x < gSurface->Width(); x++)
					{
						CSurface::ColorT* pPixel = gSurface->GetPixel(x, y);
						COLORREF c = *pPixel;
						SetPixel(hdc, x, y, c /* RGB(255, 255, 255)*/);
					}
				}
			}
			EndPaint(hWnd, &ps);
			break;
		}
	case WM_LBUTTONDOWN:
		{
			UFillSurface();
			InvalidateRect(hWnd, NULL, true);
		}break;

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
