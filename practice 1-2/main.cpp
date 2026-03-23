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
std::uniform_int_distribution<int> uidColor(0, 255);

int height;
int width;
int uidX;
int googoodan;
int* getRandPos = new int[20];

int randNum = uidColor(gen) % 2;

struct Pos
{
	int x;
	int y;
};
Pos arr[100]{};

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"My Window Class";
LPCTSTR lpszWindowName = L"windows program 4";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void createRandomPos();
void drawPos(HDC hDC);

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

		drawPos(hDC);

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
	for (int i{}; i < googoodan; ++i)
	{
		getRandPos[i] = width / googoodan * i;
	}
	uidX = getRandPos[uid(gen) % 10];
}

void drawPos(HDC hDC)
{
	googoodan = uid(gen);
	WCHAR str[100];
	
	

	if (randNum)
	{
		SetTextColor(hDC, RGB(uidColor(gen), uidColor(gen), uidColor(gen)));
	}
		
	for (int j{ 1 }; j <= 9; ++j)
	{
		wsprintf(str, L"%dx%d=%d", googoodan, j, googoodan * j);
			
		if (!randNum)
		{
			SetTextColor(hDC, RGB(uidColor(gen), uidColor(gen), uidColor(gen)));
		}
		TextOut(hDC, (uidX + j * 10) % width, (height / googoodan + j*14) % height, str, lstrlen(str));
	}
}
