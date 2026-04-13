#include "Board.h"

Board::Board()
{
	cells.resize(boardRow + boardCol);
	for (int i{}; i < boardRow; ++i)
	{
		field.resize(boardRow);
		pos.resize(boardRow);
		field[i].resize(boardCol);
		pos[i].resize(boardCol);
	}
}

void Board::initialize()
{
	int x{}, y{};
	int lenX{ ws.WIDTH / boardCol };
	int lenY{ ws.HEIGHT / boardRow };
	int dX{ ws.WIDTH / (boardCol * 2) };
	int dY{ ws.HEIGHT / (boardRow * 2) };

	for (int i{}; i < boardCol; ++i)
	{
		for (int j{}; j < boardRow; ++j)
		{
			pos[i][j] = POINT{ x + dX, y + dY };
			y += lenY;
		}
		y = 0;
		x += lenX;
	}

	// 타일 초기화
	for (int i{}; i < boardRow; ++i)
	{
		for (int j{}; j < boardCol; ++j)
		{
			field[i][j] = Shape{};
		}
	}

	// 스네이크 초기화(머리 1개)
	snake.clear();
	snake.push_back(POINT{ 0, 0 });

	Shape& head = field[0][0];
	head.setTileType(TileType::PLAYER);
	head.setShape(Type::CIRCLE, (dX > dY) ? dY : dX);
	head.setColor(uidColor(gen), uidColor(gen), uidColor(gen));
	head.push(Direction::DOWNDIR);

	// 아이템
	for (int i{}; i < 20; ++i)
	{
		while (true)
		{
			x = uid(gen) % boardCol;
			y = uid(gen) % boardCol;

			if (field[x][y].getTileType() == TileType::EMPTY)
			{
				field[x][y].setShape(Type::RECTANGLE, (dX > dY) ? dY : dX);
				field[x][y].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
				field[x][y].setTileType(TileType::ITEM);
				break;
			}
		}
	}

	// 격자선 초기화
	const int vLineCount = boardCol + 1;
	const int hLineCount = boardRow + 1;
	cells.resize(vLineCount + hLineCount);

	for (auto& c : cells) c.setType(Type::LINE);

	int idx = 0;
	for (int col = 0; col <= boardCol; ++col, ++idx)
	{
		const int px = col * lenX;

		cells[idx].setColor(255, 255, 255);
		cells[idx].setLineColor(0, 0, 0);
		cells[idx].clear();

		cells[idx].addPoint(POINT{ px, 0 });
		cells[idx].addPoint(POINT{ px, ws.HEIGHT });
	}

	for (int row = 0; row <= boardRow; ++row, ++idx)
	{
		const int py = row * lenY;

		cells[idx].setColor(255, 255, 255);
		cells[idx].setLineColor(0, 0, 0);
		cells[idx].clear();

		cells[idx].addPoint(POINT{ 0, py });
		cells[idx].addPoint(POINT{ ws.WIDTH, py });
	}
}

void Board::draw(HDC hDC) const
{
	for (const auto& c : cells)
	{
		c.draw(hDC, POINT{ 0, 0 });
	}

	for (int i{}; i < boardRow; ++i)
	{
		for (int j{}; j < boardCol; ++j)
		{
			field[i][j].draw(hDC, pos[i][j]);
		}
	}
}

POINT Board::findPlayer()
{
	if (!snake.empty())
	{
		return snake.front();
	}
	return POINT{ -1, -1 };
}

bool Board::isInside(POINT p) const
{
	return (p.x >= 0) && (p.x < boardCol) && (p.y >= 0) && (p.y < boardRow);
}

bool Board::isSnakeAt(POINT p) const
{
	for (const auto& s : snake)
	{
		if (s.x == p.x && s.y == p.y) return true;
	}
	return false;
}

POINT Board::nextPos(POINT from, Direction dir) const
{
	POINT to = from;

	if (dir == Direction::LEFTDIR) to.x -= 1;
	else if (dir == Direction::RIGHTDIR) to.x += 1;
	else if (dir == Direction::UPDIR) to.y -= 1;
	else if (dir == Direction::DOWNDIR) to.y += 1;

	return to;
}

void Board::clearSnakeTiles()
{
	for (const auto& s : snake)
	{
		field[s.x][s.y] = Shape{};
	}
}

void Board::applySnakeTiles()
{
	if (snake.empty()) return;

	// 머리
	const POINT h = snake[0];
	Shape& head = field[h.x][h.y];
	head.setTileType(TileType::PLAYER);
	head.setShape(Type::CIRCLE, ws.GetCellLen() / 4);

	// 꼬리들
	for (size_t i = 1; i < snake.size(); ++i)
	{
		const POINT t = snake[i];
		Shape& tail = field[t.x][t.y];
		tail.setTileType(TileType::CHASER);
		int tailLen{ ws.GetCellLen() / 5 - (int)i };
		tail.setShape(Type::CIRCLE, (tailLen > 0) ? tailLen : 1 );
		tail.setColor(head.getColor(0), head.getColor(1), head.getColor(2));
	}
}

void Board::processMove()
{
	if (snake.empty()) return;

	// 이동 전 좌표(지울 대상) 보관
	const std::vector<POINT> prevSnake = snake;

	const POINT headPos = snake[0];
	Shape headBackup = field[headPos.x][headPos.y]; // dir/색/모양 보존

	if (headBackup.dirSize() == 0)
	{
		return;
	}

	const Direction dir = headBackup.getDir();
	const POINT newHead = nextPos(headPos, dir);

	// 벽 충돌 처리
	if (!isInside(newHead))
	{
		field[headPos.x][headPos.y] = headBackup;

		while (field[headPos.x][headPos.y].dirSize() != 0)
		{
			field[headPos.x][headPos.y].pop();
		}

		if (newHead.x < 0)
		{
			field[headPos.x][headPos.y].push(Direction::DOWNDIR);
			field[headPos.x][headPos.y].push(Direction::RIGHTDIR);
		}
		else if (newHead.x >= boardCol)
		{
			field[headPos.x][headPos.y].push(Direction::DOWNDIR);
			field[headPos.x][headPos.y].push(Direction::LEFTDIR);
		}
		else if (newHead.y < 0)
		{
			field[headPos.x][headPos.y].push(Direction::RIGHTDIR);
			field[headPos.x][headPos.y].push(Direction::DOWNDIR);
		}
		else if (newHead.y >= boardRow)
		{
			field[headPos.x][headPos.y].push(Direction::RIGHTDIR);
			field[headPos.x][headPos.y].push(Direction::UPDIR);
		}

		return;
	}

	// 자기 몸 충돌(이동 금지)
	if (isSnakeAt(newHead))
	{
		return;
	}

	const bool ateItem = (field[newHead.x][newHead.y].getTileType() == TileType::ITEM);

	const bool ateMover = (field[newHead.x][newHead.y].getTileType() == TileType::MOVER);

	// 이동(좌표 리스트)
	const POINT oldTail = snake.back();
	for (int i = (int)snake.size() - 1; i >= 1; --i)
	{
		snake[i] = snake[i - 1];
	}
	snake[0] = newHead;

	if (ateItem)
	{
		field[oldTail.x][oldTail.y].setShape(Type::NONE);
		field[oldTail.x][oldTail.y].setTileType(TileType::EMPTY);
		createItem();
	}

	if (ateMover)
	{
		snake.push_back(oldTail);
	}

	// 1) 이동 전 좌표를 전부 지움 (잔상 제거 핵심)
	for (const auto& p : prevSnake)
	{
		field[p.x][p.y] = Shape{};
	}

	// 2) 이동 후 스네이크를 다시 그림
	field[newHead.x][newHead.y] = headBackup;
	field[newHead.x][newHead.y].setTileType(TileType::PLAYER);

	for (size_t i = 1; i < snake.size(); ++i)
	{
		const POINT t = snake[i];
		Shape& tail = field[t.x][t.y];
		tail.setTileType(TileType::CHASER);
		tail.setShape(Type::CIRCLE, ws.GetCellLen() / 5);
	}

	// dir 큐 소모
	if (field[newHead.x][newHead.y].dirSize() > 1)
	{
		field[newHead.x][newHead.y].pop();
	}
}

void Board::createItem()
{
	int x{}, y{};
	int dX{ ws.WIDTH / (boardCol * 2) };
	int dY{ ws.HEIGHT / (boardRow * 2) };
	while (true)
	{
		x = uid(gen) % boardCol;
		y = uid(gen) % boardCol;

		if (field[x][y].getTileType() == TileType::EMPTY)
		{
			field[x][y].setShape(Type::CIRCLE, (dX > dY) ? dY : dX);
			field[x][y].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
			field[x][y].setTileType(TileType::MOVER);
			field[x][y].setMoveType(uid(gen) % 5);
			break;
		}
	}
}

void Board::changeDir(Direction dir)
{
	const POINT pos = findPlayer();
	if (pos.x < 0) return;

	Shape& player = field[pos.x][pos.y];

	while (player.dirSize() != 0)
	{
		player.pop();
	}
	player.push(dir);
}
