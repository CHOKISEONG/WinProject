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

#define MAX_LINE 20

std::random_device rd;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);
std::uniform_int_distribution<int> uid(2, 20);
std::uniform_int_distribution<int> uidPos(0, HEIGHT);
std::uniform_int_distribution<int> uidColor(0, 255);

int printControl = 0;
int textColor[3]{};

SIZE size{};

typedef struct
{
	int x; int y; int number; int count;
}Text;
std::vector<Text> text;

std::wstring str;
std::wstring buffer;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"My Window Class";
LPCTSTR lpszWindowName = L"windows program 2-6";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void inputManager(WPARAM& wParam);
void drawPaint(HDC& hDC);
void initialize(HWND& hWnd);
void translateBuffer();

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
	SetBkColor(hDC, RGB(255 - textColor[0], 255 - textColor[1], 255 - textColor[2]));
	SetTextColor(hDC, RGB(textColor[0], textColor[1], textColor[2]));

	TextOut(hDC, 0, 0, buffer.c_str(), (int)buffer.size());
	GetTextExtentPoint32W(hDC, buffer.c_str(), (int)buffer.size(), &size);
	SetCaretPos(size.cx, 0);

	if (text.empty()) return;

	int startIdx = printControl ? 0 : (int)text.size() - 1;

	for (int i = startIdx; i < (int)text.size(); ++i)
	{
		str.clear();
		for (int k = 0; k < text[i].count; ++k)
		{
			str += std::to_wstring(text[i].number);
		}

		SIZE sz;
		GetTextExtentPoint32W(hDC, str.c_str(), (int)str.size(), &sz);

		for (int k = 0; k < text[i].count; ++k)
		{
			RECT r;
			r.left = text[i].x;                 
			r.top = text[i].y + (k * sz.cy);    
			r.right = r.left + sz.cx;
			r.bottom = r.top + sz.cy;

			DrawText(hDC, str.c_str(), -1, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
	}
}

void initialize(HWND& hWnd)
{
	textColor[0] = uidColor(gen); textColor[1] = uidColor(gen); textColor[2] = uidColor(gen);
	CreateCaret(hWnd, NULL, 5, 15);
	ShowCaret(hWnd);
}

void translateBuffer()
{
	std::wstringstream wss(buffer);
	int x{}, y{}, n{}, c{};

	if (wss >> x >> y >> n >> c)
	{
		text.push_back(Text{ x,y,n,c });
	}
	buffer.clear();
}

void inputManager(WPARAM& wParam)
{
	switch (wParam)
	{
	case '0':case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':
		buffer += wParam;
		break;
	case VK_BACK:
		if (buffer.size() > 0)
		{
			buffer.erase(buffer.end() - 1);
		}
		break;
	case VK_SPACE:
		buffer += ' ';
		break;
	case VK_RETURN:
		translateBuffer();
		break;
	case 'a':
		printControl = (printControl + 1) % 2;
		break;
	case 'r':
		text.clear();
		buffer.clear();
		textColor[0] = uidColor(gen); textColor[1] = uidColor(gen); textColor[2] = uidColor(gen);
		break;
	case 'q':
		exit(0);
		break;
	}
}