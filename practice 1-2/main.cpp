#include <windows.h>
#include <tchar.h>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>
#include <vector>

#define WIDTH  800
#define HEIGHT 600

#define MAX_LINE 5

std::random_device rd;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);
std::uniform_int_distribution<int> uid(2, 20);
std::uniform_int_distribution<int> uidPos(0, HEIGHT);
std::uniform_int_distribution<int> uidColor(0, 255);

int startPos[2]{};
int textColor[3]{};

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"My Window Class";
LPCTSTR lpszWindowName = L"windows program 2-5";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

// void createRandomPos();
// void drawRect(HDC hDC, LPARAM lParam);

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
	HDC hDC;
	PAINTSTRUCT ps;

	static SIZE size{};
	static TCHAR str[MAX_LINE][21];
	static int line{};
	static int count{};

	switch (uMsg) 
	{
	case WM_CREATE:
		startPos[0] = uidPos(gen); startPos[1] = uidPos(gen);
		textColor[0] = uidColor(gen); textColor[1] = uidColor(gen); textColor[2] = uidColor(gen);
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		break;
	case WM_CHAR:
		if (wParam == VK_BACK)
		{
			if (count > 0)
			{
				--count;
				str[line][count] = '\0';
			}
			else if (line > 0)
			{
				--line;
				count = lstrlen(str[line]);
			}

		}
		else if (wParam == VK_RETURN)
		{
			if (line < MAX_LINE)
			{
				startPos[1] += 20;
			}		
		}
		else if (wParam == 'r')
		{
			startPos[0] = uidPos(gen); startPos[1] = uidPos(gen);
			textColor[0] = uidColor(gen); textColor[1] = uidColor(gen); textColor[2] = uidColor(gen);
		}
		else
		{
			if (count < 20)
			{
				str[line][count] = wParam;
				++count;
				str[line][count] = '\0';
			}
			else if (line < MAX_LINE - 1)
			{
				++line;
				count = 0;
				str[line][count] = '\0';
			}
		}
		
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		
		SetTextColor(hDC, RGB(textColor[0], textColor[1], textColor[2]));

		for (int i{}; i < line + 1; ++i)
		{
			int x{ startPos[0] % WIDTH };
			int y{ (startPos[1] + (i * 15)) % HEIGHT };

			TextOut(hDC, x, y, str[i], lstrlen(str[i]));
		}
		
		GetTextExtentPoint32(hDC, str[line], count, &size);
		SetCaretPos(startPos[0] + size.cx, startPos[1] + (line * 15));
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// void createRandomPos()
// {
// 	rectX = uidRect(gen) % width;
// 	rectY = uidRect(gen) % (height / 2);
// 	rectWidth = uidRect(gen) % (width / 2);
// 	rectHeight = uidRect(gen) % (height / 2);
// }
// 
// void drawRect(HDC hDC, LPARAM lParam)
// {
// 	WCHAR str[100];
// 	int color[4][3];
// 	for (int i{}; i < 4; ++i)
// 	{
// 		for (int j{}; j < 3; ++j)
// 		{
// 			color[i][j] = uidColor(gen);
// 		}
// 	}
// 
// 	int x = rectX;
// 	int y = rectY;
// 	int width = (rectWidth > LOWORD(lParam)) ? rectWidth : 30;
// 	int height = (rectHeight > HIWORD(lParam)) ? rectHeight : 30;
// 
// 	for (int j{ x }; j < x + width; j += 10)
// 	{
// 		SetTextColor(hDC, RGB(color[0][0], color[0][1], color[0][2]));
// 		wsprintf(str, L"%c", (char)(uidChar(gen)));
// 		TextOut(hDC, j, y, str, lstrlen(str));
// 
// 		SetTextColor(hDC, RGB(color[1][0], color[1][1], color[1][2]));
// 		wsprintf(str, L"%c", (char)(uidChar(gen)));
// 		TextOut(hDC, j, y + height, str, lstrlen(str));
// 	}
// 
// 	for (int j{ y }; j < y + height; j += 14)
// 	{
// 		SetTextColor(hDC, RGB(color[2][0], color[2][1], color[2][2]));
// 		wsprintf(str, L"%c", (char)(uidChar(gen)));
// 		TextOut(hDC, x, j, str, lstrlen(str));
// 
// 		SetTextColor(hDC, RGB(color[3][0], color[3][1], color[3][2]));
// 		wsprintf(str, L"%c", (char)(uidChar(gen)));
// 		TextOut(hDC, x + width, j, str, lstrlen(str));
// 	}
// }
