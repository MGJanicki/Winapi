// WinApi.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Snake.h"
#include <time.h>

#define MAX_LOADSTRING 100
#define TIMER 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
vector<Snake*> snakes;
vector<Snake*>::iterator it;
HPEN hPen = CreatePen(PS_SOLID, 20, RGB(0, 0, 0));	//pióro o gruboœci 20 mm
HPEN hRedPen = CreatePen(PS_SOLID, 20, RGB(255, 0, 0));	//pióro o gruboœci 20 mm
Berry *berry;


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	
	srand((unsigned int)time(NULL));
	Snake* snake = new Snake(30, 10);
	snakes.push_back(snake);
	berry = new Berry();

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINAPI);
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

   hWnd = CreateWindowEx(0, szWindowClass, szTitle, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,  //flagi blokuj¹ mo¿liwoœæ zmieniania rozmiaru okna
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
		hdc = GetDC(hWnd);
		SetMapMode(hdc, MM_LOMETRIC);
		POINT p[1];
		p[0].x = 1000;
		p[0].y = -1000;
		LPtoDP(hdc, p, 1);
		DeleteDC(hdc);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, p[0].x + 10, p[0].y + 52, NULL); //Padding na ramkê
		SetTimer(hWnd, TIMER, 25, (TIMERPROC)NULL);
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
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		SetMapMode(hdc, MM_LOMETRIC);					//ustaw gruboœæ na 0,1 mm
		SelectObject(hdc, hPen);						//wybierz utworzone pióro
		for(unsigned int i = 0; i < snakes.size(); i++) snakes[i]->Draw(hdc);
		SelectObject(hdc, hRedPen);						//wybierz utworzone pióro
		berry->Draw(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		for(unsigned int i = 0; i < snakes.size(); i++) snakes[i]->Move();				//wykonaj ruch wê¿em
		for(unsigned int i = snakes.size()-1; i >= 0 && i != -1; i--) 
		{
			if(snakes[i]->Empty()) 
			{
				delete snakes[i];
				snakes.erase(snakes.begin() + i);
			}
		}
		RedrawWindow(hWnd,  NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_NOCHILDREN);	//i odœwie¿ okno
		break;
	case WM_DESTROY:
		DeleteObject(hPen);								//usuñ pióro
		DeleteObject(hRedPen);								//usuñ pióro
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_LEFT:
			for(unsigned int i = 0; i < snakes.size(); i++) snakes[i]->Turn(LEFT);
			break;
		case VK_RIGHT:
			for(unsigned int i = 0; i < snakes.size(); i++) snakes[i]->Turn(RIGHT);
			break;
		case VK_DOWN:
			PostMessage(HWND_BROADCAST, GORIGHT, 0, 0);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if(message == GOLEFT)
	{
		if(snakes.size() == 0)
		{		
			Snake* snake = new Snake(wParam);
			snakes.push_back(snake);
			SetFocus(hWnd);
		}
		else for(unsigned int i = 0; i < snakes.size(); i++) 
		{
			if(snakes[i]->GetY() == wParam) 
			{
				snakes[i]->Add(wParam);
				break;
			}
			else 
			{
				Snake* snake = new Snake(wParam);
				snakes.push_back(snake);
				SetFocus(hWnd);
			}
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
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
