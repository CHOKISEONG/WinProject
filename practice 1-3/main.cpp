#include <windows.h>
#include <tchar.h>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>

#define WIDTH 1000
#define HEIGHT 800

std::random_device rd;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);
std::uniform_int_distribution<int> uid(0, 50);

struct Pos
{
	int x;
	int y;
};
Pos arr[20]{};

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"My Window Class";
LPCTSTR lpszWindowName = L"windows program 2";

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
		createRandomPos();
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		drawPos(hDC);
		// hi

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void createRandomPos()
{
	int idx{};
	for (int i{}; i < 5; ++i)
	{
		for (int j{}; j < 5; ++j)
		{
			arr[idx].x = i * WIDTH / 5 + uid(gen);
			arr[idx].y = j * HEIGHT / 5 + uid(gen);
			++idx;
		}
	}
	std::shuffle(arr, arr + 20, gen);
}

void drawPos(HDC hDC)
{
	for (int i{}; i < 15; ++i)
	{
		Pos pos;
		pos.x = arr[i].x;
		pos.y = arr[i].y;

		WCHAR str[100];
		wsprintf(str, L"%d: (%d, %d)", i + 1, pos.x, pos.y);
		TextOut(hDC, pos.x, pos.y, str, lstrlen(str));
	}
}
