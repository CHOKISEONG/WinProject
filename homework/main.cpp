#include "Message.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"My Window Class";
LPCTSTR lpszWindowName = L"windows program";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		Message::OnCreate(hWnd);
		return 0;

	case WM_KEYDOWN:
		Message::OnKeyDown(hWnd, wParam);
		return 0;

	case WM_KEYUP:
		Message::OnKeyUp(hWnd, wParam);
		return 0;

	case WM_CHAR:
		Message::OnChar(hWnd, wParam);
		return 0;

	case WM_PAINT:
		Message::OnPaint(hWnd);
		return 0;

	case WM_SIZE:
		Message::OnSize(hWnd, (int)LOWORD(lParam), (int)HIWORD(lParam));
		return 0;

	case WM_MOUSEMOVE:
		Message::MouseMove((int)LOWORD(lParam), (int)HIWORD(lParam));
		return 0;

	case WM_LBUTTONDOWN:
		Message::LMouseDown((int)LOWORD(lParam), (int)HIWORD(lParam));
		return 0;

	case WM_LBUTTONUP:
		Message::LMouseUp((int)LOWORD(lParam), (int)HIWORD(lParam));
		return 0;

	case WM_RBUTTONDOWN:
		Message::RMouseDown((int)LOWORD(lParam), (int)HIWORD(lParam));
		return 0;

	case WM_RBUTTONUP:
		Message::RMouseUp((int)LOWORD(lParam), (int)HIWORD(lParam));
		return 0;

	case WM_LBUTTONDBLCLK:
		Message::LMouseDBClick((int)LOWORD(lParam), (int)HIWORD(lParam));
		return 0;

	case WM_RBUTTONDBLCLK:
		Message::RMouseDBClick((int)LOWORD(lParam), (int)HIWORD(lParam));
		return 0;

	case WM_COMMAND:
		Message::OnMessage(hWnd, wParam);
		return 0;

	case WM_DESTROY:
		Message::OnDestroy(hWnd);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASSEX WndClass{};
	g_hInst = hInstance;
	ws.instance = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;

	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WndClass))
	{
		return 0;
	}

	int style = WS_OVERLAPPEDWINDOW;
	int exStyle = 0;

	RECT rc{ 0, 0, ws.width, ws.height };
	AdjustWindowRectEx(&rc, style, FALSE, exStyle);

	hWnd = CreateWindow(
		lpszClass,
		lpszWindowName,
		style,
		400,
		0,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL)
	{
		return 0;
	}

	ws.hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

