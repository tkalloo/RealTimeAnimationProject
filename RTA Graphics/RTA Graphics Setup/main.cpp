#include "Windows.h"
#include <ctime> 
#include <math.h> 
#include "Renderer.h"
#include "RenderShape.h"
//#include "Utilities.h"

class DEMO_APP
{
	HINSTANCE application;
	WNDPROC wndProc;
	HWND window;
	
public: 
	Renderer * MainRenderer; 
	DEMO_APP(HINSTANCE hInst, WNDPROC proc); 
	bool Run(); 
	bool Shutdown(); 
};

DEMO_APP::DEMO_APP(HINSTANCE hinst, WNDPROC proc)
{
	application = hinst; 
	wndProc = proc; 

	WNDCLASSEX wndClass; 
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(WNDCLASSEX); 
	wndClass.lpfnWndProc = wndProc; 
	wndClass.lpszClassName = L"RTA Project"; 
	wndClass.hInstance = application; 
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME); 

	RegisterClassEx(&wndClass); 

	RECT windowSize = { 0, 0, BUFFER_WIDTH, BUFFER_HEIGHT };
	AdjustWindowRect(&windowSize, WS_OVERLAPPEDWINDOW, false); 

	window = CreateWindow(L"RTA Project", L"RTA Project", WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), CW_USEDEFAULT, CW_USEDEFAULT, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top, NULL, NULL, application, this); 
	ShowWindow(window, SW_SHOW); 

	MainRenderer->Initialize(&window); 
}

bool DEMO_APP::Run()
{
	MainRenderer->Render();
	return true; 
}

bool DEMO_APP::Shutdown()
{
	MainRenderer->Shutdown(); 
	UnregisterClass(L"RTA Project", application); 
	return true; 
}

int WINAPI wWinMain(HINSTANCE inst, HINSTANCE prevInst, LPTSTR lpCmdLine, int cmdShow); 

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam); 

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, int)
{
	srand(unsigned int(time(0))); 
	DEMO_APP app(hInst, (WNDPROC)wndProc);
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); 
	while (msg.message != WM_QUIT && app.Run())
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		//app.CameraMovement(); 
	}
	app.Shutdown(); 
	return 0; 
}

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (GetAsyncKeyState(VK_ESCAPE))
		message = WM_DESTROY; 
	if (message == WM_DESTROY)
		PostQuitMessage(0); 
	return DefWindowProc(hWnd, message, wparam, lparam); 
}
