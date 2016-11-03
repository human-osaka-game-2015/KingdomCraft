#include <windows.h>
#include <crtdbg.h>
#include <d3d11.h>
//#include <d3dx11.h>

#include "SceneManager//SceneManager.h"
#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HWND hwnd = NULL;
	WNDCLASSEX  wndclass;
	static TCHAR* szAppName = TEXT("KingdomCraft");
	
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(
		szAppName, 
		szAppName, 
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX | WS_VISIBLE,
		0,
		0,
		DEFAULT_WINDOW_WIDTH, 
		DEFAULT_WINDOW_HEIGHT, 
		NULL, 
		NULL, 
		hInst, 
		NULL);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	SetWindowText(hwnd, TEXT("KingdomCraft"));


	//ライブラリ関係

	// シーンマネージャー生成
	SceneManager* pSceneManager = new SceneManager(hwnd);

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
			if (pSceneManager->Run())
			{
				break;
			}
		}
	}
	// SceneManagerの解放
	delete pSceneManager;

	return (INT)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return  0;
		break;
	case WM_KEYDOWN:
		switch ((CHAR)wparam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
			break;
		}
		break;
	}
	return  DefWindowProc(hwnd, message, wparam, lparam);
}

