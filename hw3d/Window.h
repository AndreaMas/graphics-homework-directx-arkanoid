#pragma once

#include "WinWrap.h"
#include "Keyboard.h"
#include "Graphics.h"

class Window
{
	public:

		Window();
		~Window();

		bool ProcessMessage();

	private:

		static LRESULT CALLBACK HandleMsgSetup( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam );
		static LRESULT CALLBACK HandleMsgThunk( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam );
		LRESULT HandleMsg( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam );

	public:

		Keyboard kbd;
		Graphics gfx;

		static const int WindowWidth = 800;
		static const int WindowHeight = 800;
		const char* mWinClassName;

	private:

		HWND hWnd = nullptr;
		HINSTANCE hInst = nullptr;
};
