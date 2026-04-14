#include "Message.h"
#include "KeyHandler.h"
#include <string>

void Message::OnCreate(HWND hWnd)
{
	// event id를 관리해야할 필요가 느껴질 때 두번째 인자 수정하기
	SetTimer(hWnd, 0, TimerFuncFPS, (TIMERPROC)TimerFunc);
}

void Message::TimerFunc(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{

}

void Message::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	SetROP2(hDC, currentROP2);

	

	EndPaint(hWnd, &ps);
}

void Message::LMouseClick()
{
	
}

void Message::RMouseClick()
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
		InvalidateRect(hWnd, NULL, TRUE);
		return;
	default:
		KeyHandler::Default(hWnd, wParam);
		break;
	}

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

void Message::OnSize(HWND hWnd, int width, int height)
{
	ws.WIDTH = width;
	ws.HEIGHT = height;
	InvalidateRect(hWnd, NULL, TRUE);
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
