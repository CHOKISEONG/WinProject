#include <windows.h>
#include <tchar.h>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>
#include <vector>

#define WIDTH  1200
#define HEIGHT 600

std::random_device rd;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);
std::uniform_int_distribution<int> uid(2, 20);
std::uniform_int_distribution<char> uidChar('A', 'Z');
std::uniform_int_distribution<int> uidColor(0, 255);
std::uniform_int_distribution<int> uidRect(0, 9999);

int height;
int width;

int rectWidth;
int rectHeight;
int rectX;
int rectY;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"My Window Class";
LPCTSTR lpszWindowName = L"windows program 4";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void createRandomPos();
void drawRect(HDC hDC);

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW | WS_BORDER, 0, 0, WIDTH, HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;

	switch (uMsg) {
	case WM_CREATE:
		width = HIWORD(lParam);
		height = LOWORD(lParam);
		createRandomPos();
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		drawRect(hDC);

		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		width = HIWORD(lParam);
		height = LOWORD(lParam);
		createRandomPos();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void createRandomPos()
{
	rectWidth = uidRect(gen) % width;
	rectHeight = uidRect(gen) % height;
	rectX = uidRect(gen) % width;
	rectY = uidRect(gen) % height;
}

void drawRect(HDC hDC)
{
	WCHAR str[100];

	int color[4][3];
	for (int i{}; i < 4; ++i)
	{
		for (int j{}; j < 3; ++j)
		{
			color[i][j] = uidColor(gen);
		}
	}
	for (int j{ rectX }; j < rectX + rectWidth; j += 10)
	{
		SetTextColor(hDC, RGB(color[0][0], color[0][1], color[0][2]));
		wsprintf(str, L"%c", uidChar(gen));
		TextOut(hDC, j, rectY, str, lstrlen(str));

		SetTextColor(hDC, RGB(color[1][0], color[1][1], color[1][2]));
		wsprintf(str, L"%c", uidChar(gen));
		TextOut(hDC, j, rectY + rectHeight, str, lstrlen(str));
	}

	for (int j{ rectY }; j < rectY + rectHeight; j += 14)
	{
		SetTextColor(hDC, RGB(color[2][0], color[2][1], color[2][2]));
		wsprintf(str, L"%c", uidChar(gen));
		TextOut(hDC, rectX, j, str, lstrlen(str));

		SetTextColor(hDC, RGB(color[3][0], color[3][1], color[3][2]));
		wsprintf(str, L"%c", uidChar(gen));
		TextOut(hDC, rectX + rectWidth, j, str, lstrlen(str));
	}
}
