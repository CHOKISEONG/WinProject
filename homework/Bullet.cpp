#include "Bullet.h"
#include "Board.h"
#include "Pacman.h"

void eraseBullet()
{
	for (int i{}; i < (int)bullets.size(); ++i)
	{
		if (bullets[i].pos.x < 0 || bullets[i].pos.x > ws.width || bullets[i].pos.y < 0 || bullets[i].pos.y > ws.height)
		{
			bullets.erase(bullets.begin() + i);
			--i;
		}
	}
}

void checkBullet()
{
	for (int i{}; i < (int)bullets.size(); ++i)
	{
		for (int j{}; j < (int)board.itemPos.size(); ++j)
		{
			if (getDistance(bullets[i].pos, board.itemPos[j]) < board.items[j].getLength())
			{		
				for (int k{}; k < 2; ++k)
				{
					POINT tmp{ uid(gen) % 80 - 40 + board.itemPos[j].x, uid(gen) % 80 - 40 + board.itemPos[j].y };
					board.makeItem(tmp);
				}

				bullets.erase(bullets.begin() + i);
				--i;
				board.itemPos.erase(board.itemPos.begin() + j);
				board.items.erase(board.items.begin() + j);
				--j;
				break;
			}
		}
	}

	for (int i{}; i < (int)bullets.size(); ++i)
	{
		for (int j{}; j < (int)board.collideRect.size(); ++j)
		{
			if (PtInRect(&board.collideRect[j], bullets[i].pos))
			{
				player.speed += 1.0f;

				bullets.erase(bullets.begin() + i);
				--i;
				board.collide.erase(board.collide.begin() + j);
				board.collidePos.erase(board.collidePos.begin() + j);
				board.collideRect.erase(board.collideRect.begin() + j);
				--j;
				break;
			}
		}
	}
}
