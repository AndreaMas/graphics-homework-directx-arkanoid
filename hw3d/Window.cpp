#include "Window.h"
#include <iostream>
#include <assert.h>

// Window Stuff
Window::Window():
	hInst(GetModuleHandle(nullptr))
{
	// Set win title

	mWinClassName = "Arkanoid";

	// Create & register window class
	
	WNDCLASSEX winc = { 0 };
	winc.cbSize = sizeof(winc);
	winc.style = CS_OWNDC;
	winc.lpfnWndProc = HandleMsgSetup;
	winc.cbClsExtra = 0;
	winc.cbWndExtra = 0;
	winc.hInstance = hInst;
	//wc.hIcon = LoadIcon( hInst, MAKEINTRESOURCE( IDI_ICON1 ), IMAGE_ICON, 32, 32, 0 ));
	//wc.hIconSm = LoadIcon( LoadImage( hInst, MAKEINTRESOURCE( IDI_ICON1 ), IMAGE_ICON, 16, 16, 0 ));
	winc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(101));
	winc.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(101));
	winc.hCursor = nullptr;
	winc.hbrBackground = nullptr;
	winc.lpszMenuName = nullptr;
	winc.lpszClassName = mWinClassName;

	RegisterClassEx(&winc);

	// Calculate window size based on desired client region size

	RECT wrect;
	wrect.left = 100;
	wrect.right = WindowWidth + wrect.left;
	wrect.top = 100;
	wrect.bottom = WindowHeight + wrect.top;

	AdjustWindowRect( &wrect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE );

	// create window & get hWnd

	hWnd = CreateWindow(
		mWinClassName,
		mWinClassName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrect.right - wrect.left,wrect.bottom - wrect.top,
		nullptr,nullptr,
		hInst,
		this
	);
	assert(hWnd != nullptr);

	// Initialize Graphics

	gfx.Initialize(hWnd);

	// Show window

	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow(hWnd);
}

Window::~Window()
{
	UnregisterClass(mWinClassName, hInst); // TODO: before or after?
	DestroyWindow( hWnd );
}

bool Window::ProcessMessage()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}
	return true;
}

LRESULT CALLBACK Window::HandleMsgSetup( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam )
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if( msg == WM_NCCREATE )
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr( hWnd,GWLP_USERDATA,reinterpret_cast<LONG_PTR>(pWnd) );
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr( hWnd,GWLP_WNDPROC,reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk) );
		// forward message to window instance handler
		return pWnd->HandleMsg( hWnd,msg,wParam,lParam );
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc( hWnd,msg,wParam,lParam );
}

LRESULT CALLBACK Window::HandleMsgThunk( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam )
{
	// retrieve ptr to window instance
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr( hWnd,GWLP_USERDATA ));
	// forward message to window instance handler
	return pWnd->HandleMsg( hWnd,msg,wParam,lParam );
}

LRESULT Window::HandleMsg( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam )
{
	switch( msg )
	{
		case WM_CLOSE:
			// Don't want the DefWindowProc to handle close message,
			// return 0 to call window destructor instead
			PostQuitMessage( 0 );
			return 0;
		/*********** KEYBOARD MESSAGES ***********/
		case WM_KEYDOWN:
			if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) // avoids autorepeat?
			{
				kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
			}
			break;
		case WM_KEYUP:
			kbd.OnKeyReleased( static_cast<unsigned char>(wParam) );
			break;
		case WM_CHAR:
			kbd.OnChar( static_cast<unsigned char>(wParam) );
			break;
		/*********** END KEYBOARD MESSAGES ***********/
	}

	return DefWindowProc( hWnd,msg,wParam,lParam );
}
