#include "Message.h"
#include "KeyHandler.h"
#include "Board.h"
#include <string>

void Message::OnCreate(HWND hWnd)
{
	board.initialize();
	SetTimer(hWnd, playerAnimEvent, 1000 / playerAnimFPS, (TIMERPROC)SnakeTimer);
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
		KeyHandler::Default(wParam);
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

void Message::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	SetROP2(hDC, currentROP2);

	board.draw(hDC);

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
	const int cellW = ws.WIDTH / boardCol;
	const int cellH = ws.HEIGHT / boardRow;

	const int col = ws.mouse.x / cellW;
	const int row = ws.mouse.y / cellH;

	if (col < 0 || col >= boardCol || row < 0 || row >= boardRow)
	{
		return;
	}

	Shape& tile = board.getTile(POINT{ col,row });
	TileType type = tile.getTileType();

	if (type == TileType::EMPTY)
	{
		// 마우스가클릭된방향으로주인공원이이동방향을바꾸고다시지그재그로이동
		POINT playerPos = board.findPlayer();

		if (playerPos.x < col)
		{
			board.changeDir(Direction::RIGHTDIR);
		}
		else
		{
			board.changeDir(Direction::LEFTDIR);
		}
	}
	else if (type == TileType::PLAYER)
	{
		//꼬리원들이모두사라진다.주인공원은모양을삼각형으로
		//로이동한다.다시주인공원내부를클릭하면삼각형이다시원으로모양이바뀐다.

		board.explodeSnake();
	}
	else if (type == TileType::CHASER)
	{
		// 꼬리원은주인공원에서분리되어보드의칸에남겨지며이동한다.분리된꼬리원은앞페이지
		board.seperateSnake(POINT{col,row});
	}
}

void Message::RMouseClick()
{
	if (board.checkObstacleNum() >= 20) return;

	const int cellW = ws.WIDTH / boardCol;
	const int cellH = ws.HEIGHT / boardRow;

	const int col = ws.mouse.x / cellW;
	const int row = ws.mouse.y / cellH;

	if (col < 0 || col >= boardCol || row < 0 || row >= boardRow)
	{
		return;
	}

	board.createItem(TileType::OBSTACLE, col, row);
}

void Message::LMouseDBClick()
{
}

void Message::RMouseDBClick()
{
}

void Message::SnakeTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	if (isGameStarted)
	{
		board.moverMove();
		board.processMove();
		board.applySnakeTiles();
		InvalidateRect(hWnd, NULL, TRUE);
	}
}

void Message::OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}
