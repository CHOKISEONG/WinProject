#include <windows.h>
#include <tchar.h>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>
#include <vector>
#include <sstream>

#define WIDTH  800
#define HEIGHT 600

#define MAX_LINE 10
#define MAX_LETTER 30

std::random_device rd;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);
std::uniform_int_distribution<int> uid(2, 20);
std::uniform_int_distribution<int> uidPos(0, HEIGHT);
std::uniform_int_distribution<int> uidColor(0, 255);

int textColor[3]{};

SIZE size{};

std::wstring str;
TCHAR buffer[MAX_LINE][MAX_LETTER+1]{};

struct Pos
{
	int x; int y;
};
Pos pos{};

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"My Window Class";
LPCTSTR lpszWindowName = L"windows program 2-7";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void inputManager(WPARAM& wParam);
void drawPaint(HDC& hDC);
void initialize(HWND& hWnd);

int checkLetterCnt(int line);

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

	switch (uMsg) 
	{
	case WM_CREATE:
		initialize(hWnd);
		break;
	case WM_CHAR:
		inputManager(wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		
		drawPaint(hDC);
		
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

void drawPaint(HDC& hDC)
{
	SetTextColor(hDC, RGB(textColor[0], textColor[1], textColor[2]));

	for (int i{}; i < MAX_LINE; ++i)
	{
		int letterCnt = checkLetterCnt(i);

		if (letterCnt != 0)
		{
			GetTextExtentPoint32W(hDC, buffer[i], letterCnt, &size);
			TextOutW(hDC, 0, size.cy * i, buffer[i], letterCnt);
		}
	}

	GetTextExtentPoint32W(hDC, buffer[pos.y], pos.x + 1, &size);
	SetCaretPos(size.cx - 8, size.cy * pos.y);
}

void initialize(HWND& hWnd)
{
	for (int i{}; i < MAX_LINE; ++i)
	{
		for (int j{}; j < MAX_LETTER; ++j)
		{
			buffer[i][j] = NULL;
		}
	}
	pos.x = 0;
	pos.y = 0;
	CreateCaret(hWnd, NULL, 3, 15);
	ShowCaret(hWnd);
}

int checkLetterCnt(int line)
{
	int letterCnt = MAX_LETTER;

	for (int j{ MAX_LETTER - 1 }; j >= 0; --j)
	{
		if (buffer[line][j] != NULL)
			break;
		--letterCnt;
	}

	return letterCnt;
}

void inputManager(WPARAM& wParam)
{
	switch (wParam)
	{	
	case VK_ESCAPE:
		for (int i{}; i < MAX_LINE; ++i)
		{
			for (int j{}; j < MAX_LETTER; ++j)
			{
				buffer[i][j] = NULL;
			}
		}
		pos.x = 0;
		pos.y = 0;
		break;
	case VK_BACK:
		if (pos.y > 0 && pos.x == 0)
		{
			--pos.y;
			pos.x = checkLetterCnt(pos.y);
		}
		else if (pos.x != 0)
		{
			--pos.x;
		}
		buffer[pos.y][pos.x] = NULL;
		break;
	case VK_RETURN:
		pos.y = (pos.y + 1) % MAX_LINE;
		pos.x = 0;
		break;
	case 'q':
		exit(0);
		break;
	default:
		if (pos.x < MAX_LETTER)
		{
			buffer[pos.y][pos.x] = wParam;
			++pos.x;
		}
		else
		{
			++pos.y;
			pos.x = 0;
			if (pos.y == MAX_LINE)
			{
				pos.y = 0;
			}
			buffer[pos.y][pos.x] = wParam;
		}
		break;
	}
}