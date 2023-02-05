#include "WinWrap.h"
#include "Window.h"
#include "Application.h"
#include "Color.h"

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	Window wnd;
	Application app(wnd);

	return app.Run();
}

