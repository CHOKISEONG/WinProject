#include "Message.h"
#include "KeyHandler.h"
#include "Board.h"
#include <string>

void Message::OnCreate(HWND hWnd)
{
	// event id를 관리해야할 필요가 느껴질 때 두번째 인자 수정하기
	SetTimer(hWnd, 0, TimerFuncFPS, (TIMERPROC)TimerFunc);

	board.initialize();
}

void Message::TimerFunc(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	
}

void Message::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	HDC mDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, ws.width, ws.height);
	SelectObject(mDC, (HBITMAP)hBitmap);

	SetROP2(mDC, currentROP2);

	board.draw(mDC);
	
	BitBlt(hDC, 0, 0, ws.width, ws.height, mDC, 0, 0, SRCCOPY);
	DeleteDC(mDC);
	DeleteObject(hBitmap);

	EndPaint(hWnd, &ps);
}

void Message::LMouseDown()
{
}

void Message::LMouseUp()
{
}

void Message::RMouseDown()
{
}

void Message::RMouseUp()
{
}

void Message::LMouseDBClick()
{
}

void Message::RMouseDBClick()
{
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
	case VK_OEM_PLUS: case VK_OEM_MINUS:
		KeyHandler::KeyDown(hWnd, wParam);
		InvalidateRect(hWnd, NULL, FALSE);
		return;
	default:
		KeyHandler::Default(hWnd, wParam);
		break;
	}

	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnKeyUp(HWND hWnd, WPARAM wParam)
{
	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnChar(HWND hWnd, WPARAM wParam)
{
	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnSize(HWND hWnd, int width, int height)
{
	ws.width = width;
	ws.height = height;
	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnMessage(HWND hWnd, WPARAM wParam)
{
	return;
}

void Message::MouseMove(int mouse_x, int mouse_y)
{
	ws.mousePos.x = mouse_x;
	ws.mousePos.y = mouse_y;
}

void Message::OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}
