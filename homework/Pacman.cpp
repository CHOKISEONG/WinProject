#include "Pacman.h"
#include "Board.h"

void Pacman::initialize()
{
	load(10);
	pos = { 100,100 };
	bWidth = bHeight = 32;
	rad = 32;
	tintColor = targetColor = RGB(255, 255, 0);
}

void Pacman::move()
{
	pos.x += dir.x * speed;
	pos.y += dir.y * speed;

	if (pos.x < 0 || pos.x > ws.width || pos.y < 0 || pos.y > ws.height)
	{
		pos.x -= dir.x * speed;
		pos.y -= dir.y * speed;
	}
	else
	{
		for (int i{}; i < (int)board.collideRect.size(); ++i)
		{
			if (PtInRect(&board.collideRect[i], pos))
			{
				pos.x -= dir.x * speed;
				pos.y -= dir.y * speed;
				break;
			}
		}
	}

	int r = rad - 3;
	RECT rt = getRect();

	for (int i = static_cast<int>(board.itemPos.size()) - 1; i >= 0; --i)
	{
		auto& b = board.itemPos[i];

		if (PtInRect(&rt, b))
		{
			board.itemPos.erase(board.itemPos.begin() + i);
			tintColor = board.items[i].getColorBrush();
			board.items.erase(board.items.begin() + i);
			rad += 2;
		}
	}
}

void Pacman::animation()
{
	animT += 0.1f;
	if (animT > 2.0f)
	{
		animT = 0.0f;
	}

	if (dir.x == 0)
	{
		if (dir.y > 0)
		{
			bPos.y = bHeight * 3;
		}
		else if (dir.y < 0)
		{
			bPos.y = bHeight * 2;
		};

		if (animT < 1.0f)
		{
			bPos.x = 0;
		}
		else
		{
			bPos.x = bWidth;
		}
	}
	else if (dir.y == 0)
	{
		if (dir.x > 0)
		{
			bPos.y = 0;
		}
		else if (dir.x < 0)
		{
			bPos.y = bHeight;
		};

		if (animT < 1.0f)
		{
			bPos.x = 0;
		}
		else
		{
			bPos.x = bWidth;
		}
	}

	if (otherAnim)
	{
		bPos.y = bHeight * 4;
	}
}

void OtherAnimTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	static float t = 0.0f;
	t += 0.01f;
	if (t < 1.0f)
	{
		player.otherAnim = true;
	}
	else
	{
		player.otherAnim = false;
		t = 0.0f;
		KillTimer(hWnd, 1);
	}
}
