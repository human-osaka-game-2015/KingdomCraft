#include <Windows.h>
#include <crtdbg.h>
#include "Scene\Scene.h"


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE _hInst, HINSTANCE _hPrevInst, LPSTR _szStr, INT _iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HWND hWnd = NULL;
	static LPTSTR szAppName = TEXT("ParameterTool");
	static const int WindowWidth = 1280;
	static const int WindowHeight = 720;
	WNDCLASSEX  wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = _hInst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	hWnd = CreateWindow(
		szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX | WS_VISIBLE,
		0,
		0,
		WindowWidth,
		WindowHeight,
		NULL,
		NULL,
		_hInst,
		NULL);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetWindowText(hWnd, TEXT("ParameterTool"));

	Scene* pScene = new Scene(hWnd, _hInst);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			pScene->Run();
		}
	}

	delete pScene;

	return (INT)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam)
{
	switch (_message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return  DefWindowProc(_hwnd, _message, _wparam, _lparam);
}