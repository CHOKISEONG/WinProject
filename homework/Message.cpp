#include "Message.h"
#include "KeyHandler.h"
#include "Board.h"
#include "resource.h"
#include "Image.h"
#include "Block.h"
#include "Cat.h"
#include "Food.h"
#include <string>
#include <algorithm>

void Message::OnCreate(HWND hWnd)
{
	// event id를 관리해야할 필요가 느껴질 때 두번째 인자 수정하기
	SetTimer(hWnd, 0, 1000 / TimerFuncFPS, (TIMERPROC)TimerFunc);

	cat.load(0);
	cat.initialize();
	cat.pos = { ws.width / 2, ws.height / 2 };
	rat.load(1);
	rat.rad = rat.rad / 2;
	background.pos = { ws.width / 2, ws.height / 2 };
	background.rad = max(ws.width, ws.height);
	background.load(2);
	ws.makeOOWRect();

	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::TimerFunc(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	static float t = 0.0f;
	t += 0.1f;

	if (t >= 0.3f)
	{
		cat.animate();
		t = 0.0f;
	}

	if (!foods.empty())
	{
		cat.move(2, foods.back().pos);
		if (foods.back().pos.x - foods.back().rad < cat.pos.x && cat.pos.x < foods.back().pos.x + foods.back().rad &&
			foods.back().pos.y - foods.back().rad < cat.pos.y && cat.pos.y < foods.back().pos.y + foods.back().rad)
			{
				foods.pop_back();
				cat.changeSpeed(0.3f);
			}
	}
	else
		cat.moves();

	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	// ai도움 많이 받음
	RECT rect;
	GetClientRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, width, height);
	HBITMAP hOldMemBitmap = (HBITMAP)SelectObject(hMemDC, hMemBitmap);

	FillRect(hMemDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

	HDC mDC = CreateCompatibleDC(hDC);

	background.draw(hMemDC, mDC);

	if (ratDraw)
		rat.draw(hMemDC, mDC);

	for (auto& food : foods)
		food.draw(hMemDC, mDC);

	cat.draw(hMemDC, mDC);

	BitBlt(hDC, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);

	DeleteDC(mDC);

	SelectObject(hMemDC, hOldMemBitmap);
	DeleteObject(hMemBitmap);
	DeleteDC(hMemDC);

	EndPaint(hWnd, &ps);
}

void Message::LMouseDown(int mouse_x, int mouse_y)
{
	ws.mousePos.x = mouse_x;
	ws.mousePos.y = mouse_y;

	ratDraw = true;
	rat.pos = ws.mousePos;
}

void Message::LMouseUp(int mouse_x, int mouse_y)
{
	ws.mousePos.x = mouse_x;
	ws.mousePos.y = mouse_y;

	ratDraw = false;
	rat.pos = ws.mousePos;
}

void Message::MouseMove(int mouse_x, int mouse_y)
{
	ws.mousePos.x = mouse_x;
	ws.mousePos.y = mouse_y;

	rat.pos = ws.mousePos;

}

void Message::RMouseDown(int mouse_x, int mouse_y)
{
	foods.push_back(Food({ mouse_x, mouse_y }));
}

void Message::RMouseUp(int mouse_x, int mouse_y)
{
}

void Message::LMouseDBClick(int mouse_x, int mouse_y)
{

}

void Message::RMouseDBClick(int mouse_x, int mouse_y)
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
	keyboard[tolower(wParam)] = true;

	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnKeyUp(HWND hWnd, WPARAM wParam)
{
	keyboard[tolower(wParam)] = false;
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
	ws.makeOOWRect();
	InvalidateRect(hWnd, NULL, FALSE);
}

void Message::OnMessage(HWND hWnd, WPARAM wParam)
{
}

void Message::OnDestroy(HWND hWnd)
{
	Image::ReleaseCachedBitmaps();
	PostQuitMessage(0);
}
