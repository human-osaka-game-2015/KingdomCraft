#include <windows.h>
#include <crtdbg.h>
#include "SceneManager\SceneManager.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HWND hwnd = NULL;
	WNDCLASSEX  Wndclass;
	static TCHAR* AppName = TEXT("KingdomCraft");
	
	Wndclass.cbSize = sizeof(Wndclass);
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WindowProc;
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInst;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = AppName;
	Wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&Wndclass);

	hwnd = CreateWindow(
		AppName,
		AppName,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX | WS_VISIBLE,
		0,
		0,
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		NULL, 
		NULL, 
		hInst, 
		NULL);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	SetWindowText(hwnd, TEXT("KingdomCraft"));


	SceneManager* pSceneManager = new SceneManager(hwnd);

	MSG Msg;
	ZeroMemory(&Msg, sizeof(Msg));
	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			if (pSceneManager->Run())
			{
				break;
			}
		}
	}

	delete pSceneManager;

	return (INT)Msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_KEYDOWN:
		switch (static_cast<CHAR>(_wParam))
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
			break;
		}
		break;
	}

	return DefWindowProc(_hwnd, _message, _wParam, _lParam);
}

