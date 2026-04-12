#include "Message.h"
#include "KeyHandler.h"

void Message::OnCreate(HWND hWnd)
{
	shapeInitialize();
	SetTimer(hWnd, 3, 20, (TIMERPROC)TimerProc);
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

	SetROP2(hDC, currentROP2);

	for (int i{}; i < 4; ++i)
	{
		for (int j{}; j < 4; ++j)
		{
			shapes[i][j].draw(hDC);
		}
	}

	EndPaint(hWnd, &ps);
}

void Message::OnSize(HWND hWnd, int width, int height)
{
	ws.WIDTH = width;
	ws.HEIGHT = height;
	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::MouseMove(int mouse_x, int mouse_y)
{
	ws.mouse.x = mouse_x;
	ws.mouse.y = mouse_y;
}

void Message::LMouseClick()
{
	if (progressDirDelta == 1.0f)
	{
		progressDirDelta = 1.01f;
	}
	else
	{
		progressDirDelta = 1.0f;
	}
}

void Message::RMouseClick()
{
	if (selectedShapes < 0 || selectedShapes >= 4) return;

	rButtonClicked = !rButtonClicked;

	if (rButtonClicked)
	{
		setPosAll(selectedShapes, Vec2{ (double)ws.mouse.x, (double)ws.mouse.y });
	}
	else
	{
		int idx = selectedShapes;
		if (idx == 0)
		{
			setPosAll(selectedShapes, Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.25 });
		}
		else if (idx == 1)
		{
			setPosAll(selectedShapes, Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.25 });
		}
		else if (idx == 2)
		{
			setPosAll(selectedShapes, Vec2{ ws.WIDTH * 0.25, ws.HEIGHT * 0.75 });
		}
		else if (idx == 3)
		{
			setPosAll(selectedShapes, Vec2{ ws.WIDTH * 0.75, ws.HEIGHT * 0.75 });
		}
	}
}

void Message::LMouseDBClick()
{
}

void Message::RMouseDBClick()
{
	for (int i{}; i < 4; ++i)
	{
		const Vec2 base = shapes[i][0].getPos();

		const int x0 = shapes[i][0].points[0].x + (int)base.x;
		const int y0 = shapes[i][0].points[0].y + (int)base.y;
		const int x2 = shapes[i][0].points[2].x + (int)base.x;
		const int y2 = shapes[i][0].points[2].y + (int)base.y;

		RECT rc{};
		rc.left = min(x0, x2);
		rc.right = max(x0, x2);
		rc.top = min(y0, y2);
		rc.bottom = max(y0, y2);

		if (PtInRect(&rc, POINT{ ws.mouse.x, ws.mouse.y }))
		{
			for (int j{}; j < 4; ++j)
			{
				shapes[i][j].invertColor();
			}
		}
	}
}

void Message::TimerProc(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	for (int i{}; i < 4; ++i)
	{
		shapes[i][2].setPos(shapes[i][1].getPos(shapes[i][2].getProgress()));
		shapes[i][2].updateProgress(1.0f);
	}
	
	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}
