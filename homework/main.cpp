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
		break;
	case WM_KEYDOWN:
		Message::OnKeyDown(hWnd, wParam);
		break;
	case WM_KEYUP:
		Message::OnKeyUp(hWnd, wParam);
		break;
	case WM_CHAR:
		Message::OnChar(hWnd, wParam);
		break;
	case WM_PAINT:
		Message::OnPaint(hWnd);
		break;
	case WM_SIZE:
		Message::OnSize(hWnd, (int)LOWORD(lParam), (int)HIWORD(lParam));
		break;
	case WM_DESTROY:
		Message::OnDestroy(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;

	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
	// IDI_APPLICATION / IDI_ASTERISK / IDI_EXCLAMATION / IDI_HAND / IDI_QUESTION
	// IDI_ERROR / IDI_WARNING / IDI_INFORMATION

	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	// IDC_APPSTARTING / IDC_ARROW / IDC_CROSS / IDC_HAND / IDC_HELP
	// IDD_IBEAM / IDC_SIZEALL / IDC_SIZENESW / IDC_SIZENS / IDC_SIZENWSE
	// IDC_SIZEWE / IDC_UPARROW / IDC_WAIT

	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	int style = WS_OVERLAPPEDWINDOW;
	int exStyle = 0;

	RECT rc{ 0, 0, ws.WIDTH, ws.HEIGHT }; // ws를 "원하는 클라이언트 크기"로 취급
	AdjustWindowRectEx(&rc, style, FALSE, exStyle);

	hWnd = CreateWindow(
		lpszClass,
		lpszWindowName,
		style,
		0,
		0,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

