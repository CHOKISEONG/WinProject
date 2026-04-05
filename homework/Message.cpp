#include "Message.h"
#include "KeyHandler.h"
#include "MyString.h"

void Message::OnCreate(HWND hWnd)
{
	shapes.push_back(Shape(POINT(ws.WIDTH / 2,ws.HEIGHT / 2), uid(gen),uid(gen),uid(gen)));
	shapes[0].addPoint(POINT{ -10, -10 });
	shapes[0].addPoint(POINT{ 10, -10 });
	shapes[0].addPoint(POINT{ 10, 10 });
	shapes[0].addPoint(POINT{ -10, 10 });
}

void Message::OnKeyDown(HWND hWnd, WPARAM wParam)
{
	switch (wParam)
	{
	case VK_UP:case VK_DOWN:case VK_LEFT:case VK_RIGHT:
	case VK_ESCAPE:case VK_BACK:case VK_RETURN:case VK_TAB:
	case VK_HOME:case VK_END:case VK_INSERT:
	case VK_DELETE:case VK_PRIOR:case VK_NEXT:
	case VK_F1:case VK_F2:case VK_F3:case VK_F4:
	case VK_F5:case VK_F6:case VK_F7:case VK_F8:
		KeyHandler::KeyDown(wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		return;
	default:
		break;
	}

	KeyHandler::KeyDown(wParam);
	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnKeyUp(HWND hWnd, WPARAM wParam)
{
	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnChar(HWND hWnd, WPARAM wParam)
{
	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	POINT point[3];

	point[0].x = ws.WIDTH * 0.5f;
	point[0].y = 0;

	point[1].x = ws.WIDTH * 0.9f;
	point[1].y = ws.HEIGHT * 0.9f;

	point[2].x = 0;
	point[2].y = ws.HEIGHT * 0.9f;

	for (int i{}; i < 2; ++i)
	{
		printStr(hDC, point[i], point[i + 1]);
	}
	printStr(hDC, point[2], point[0]);
	
	for (const auto& s : shapes)
	{
		s.draw(hDC);
	}

	EndPaint(hWnd, &ps);
}

void Message::OnSize(HWND hWnd, int width, int height)
{
	ws.WIDTH = width;
	ws.HEIGHT = height;
	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}
