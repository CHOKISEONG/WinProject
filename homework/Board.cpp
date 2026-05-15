#include "Board.h"
#include <numeric>

void Board::initialize()
{
	pos.resize(boardCol);
	for (int i{}; i < boardCol; ++i)
	{
		pos[i].resize(boardCol);
		for (int y{}; y < boardRow; ++y)
		{
			pos[i][y] = POINT{ i * cell + rad, y * cell + rad };
		}
	}
}

void Board::draw(HDC hDC, HDC mDC)
{
	for (int i{}; i < (int)items.size(); ++i)
	{
		items[i].draw(hDC, itemPos[i]);
	}

	for (int i{}; i < (int)collide.size(); ++i)
	{
		collide[i].draw(hDC, collidePos[i]);
	}
}

void Board::makeCollide(int num)
{
	collide.clear();
	collidePos.clear();
	collideRect.clear();
	indices.clear();
	indices.resize(boardRow * boardCol);

	std::iota(indices.begin(), indices.end(), 0);
	std::shuffle(indices.begin(), indices.end(), gen);

	for (int i{}; i < num; ++i)
	{
		collide.push_back(Shape());
		collide.back().setShape(Shape::Type::RECTANGLE, rad);
		collide.back().setColorBrush(RGB(0, 0, 255));

		const int col = indices[i] % boardCol;
		const int row = indices[i] / boardCol;

		collidePos.push_back(POINT{ col * cell + rad, row * cell + rad });

		collideRect.push_back(RECT{ collidePos.back().x - rad, collidePos.back().y - rad, collidePos.back().x + rad, collidePos.back().y + rad});
	}

	indices.erase(indices.begin(), indices.begin() + num);
}

void Board::makeItem(int num)
{
	if (dontMakeItem) return;

	for (int i{}; i < num; ++i)
	{
		items.push_back(Shape());
		items.back().setShape(Shape::Type::CIRCLE, rad/5);
		items.back().setColorBrush(RGB(uidColor(gen), uidColor(gen), uidColor(gen)));

		const int col = indices[i] % boardCol;
		const int row = indices[i] / boardCol;

		itemPos.push_back(POINT{ col * cell + rad, row * cell + rad });
	}

	std::rotate(indices.begin(), indices.begin() + num, indices.end());
}

void Board::makeItem(POINT p)
{
	if (dontMakeItem) return;

	items.push_back(Shape());
	items.back().setShape(Shape::Type::CIRCLE, rad / 5);
	items.back().setColorBrush(RGB(uidColor(gen), uidColor(gen), uidColor(gen)));
	itemPos.push_back(p);
}

void Board::deleteAllItems()
{
	dontMakeItem = true;
	KillTimer(ws.hWnd, 10);
	SetTimer(ws.hWnd, 10, 100, (TIMERPROC)ExplodeTimer);
}

void ExplodeTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	static int t = 0;
	t += 1;

	if (t > 10)
	{
		board.itemPos.clear();
		board.items.clear();
		board.dontMakeItem = false;
		KillTimer(ws.hWnd, 10);
		t = 0;
	}
	else
	{
		int rnd{ uid(gen) % 2 };

		for (auto& b : board.items)
		{
			if (rnd)
				b.setShape(Shape::Type::TRIANGLE, b.getLength());
			else
				b.setShape(Shape::Type::CIRCLE, b.getLength());

			b.setColorBrush(RGB(uidColor(gen) + t*30, uidColor(gen) + t * 30, uidColor(gen) + t * 30));
			b.setColorPen(RGB(uidColor(gen) + t * 30, uidColor(gen) + t * 30, uidColor(gen) + t * 30));
		}
	}
}
