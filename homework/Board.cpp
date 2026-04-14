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

	// 스네이크 
	snake.clear();
	snake.push_back(POINT{ uid(gen) % boardCol, uid(gen) % boardRow});

	Shape& head = field[snake[0].x][snake[0].y];
	head.setTileType(TileType::PLAYER);
	head.setShape(Type::CIRCLE, ws.GetCellLen() / 2);
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

bool Board::checkCollide(POINT from, POINT to)
{
	if (!isInside(to))
	{
		Shape& target = field[from.x][from.y];
		while (target.dirSize() != 0)
		{
			target.pop();
		}

		if (to.x < 0)
		{
			if (target.getMoveType() == 1)
			{
				while (target.dirSize() != 0)
					target.pop();

				target.push(Direction::RIGHTDIR);
			}
			else
			{
				target.push(Direction::DOWNDIR);
				target.push(Direction::RIGHTDIR);
			}
		}
		else if (to.x >= boardCol)
		{
			if (target.getMoveType() == 1)
			{
				while (target.dirSize() != 0)
					target.pop();

				target.push(Direction::LEFTDIR);
			}
			else
			{
				target.push(Direction::DOWNDIR);
				target.push(Direction::LEFTDIR);
			}
		}
		else if (to.y < 0)
		{
			if (target.getMoveType() == 2)
			{
				while (target.dirSize() != 0)
					target.pop();

				target.push(Direction::DOWNDIR);
			}
			else
			{
				target.push(Direction::RIGHTDIR);
				target.push(Direction::DOWNDIR);
			}
			
		}
		else if (to.y >= boardRow)
		{
			if (target.getMoveType() == 2)
			{
				while (target.dirSize() != 0)
					target.pop();

				target.push(Direction::UPDIR);
			}
			else
			{
				// 보드판 우하단에 가면 멈춰있는 경우 해결용
				if (to.x == boardCol - 1)
				{
					target.push(Direction::LEFTDIR);
				}
				else
				{
					target.push(Direction::RIGHTDIR);
					target.push(Direction::UPDIR);
				}
			}
		}
		
		return true;
	}
	else if (isObstacle(to))
	{
		Shape& target = field[from.x][from.y];
		while (target.dirSize() != 0)
		{
			target.pop();
		}

		Direction dir;
		if (from.x == to.x)
		{
			if (from.y > to.y)
			{
				target.push(Direction::RIGHTDIR);
				target.push(Direction::UPDIR);
			}
			else
			{
				target.push(Direction::LEFTDIR);
				target.push(Direction::DOWNDIR);
			}
		}
		if (from.y == to.y)
		{
			if (from.x > to.x)
			{
				target.push(Direction::DOWNDIR);
				target.push(Direction::LEFTDIR);
			}
			else
			{
				target.push(Direction::DOWNDIR);
				target.push(Direction::RIGHTDIR);
			}
		}

		return true;
	}

	return false;
}

int Board::checkObstacleNum()
{
	int num{};
	for (int i{}; i < boardRow; ++i)
	{
		for (int j{}; j < boardCol; ++j)
		{
			if (field[i][j].getTileType() == TileType::OBSTACLE)
				++num;
		}
	}
	return num;
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

bool Board::isObstacle(POINT p) const
{
	if (field[p.x][p.y].getTileType() == TileType::OBSTACLE)
		return true;
	return false;
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

	// 꼬리들
	for (size_t i = 1; i < snake.size(); ++i)
	{
		const POINT t = snake[i];
		Shape& tail = field[t.x][t.y];
		tail.setTileType(TileType::CHASER);
		int tailLen{ ws.GetCellLen() / 2 - (int)(i*2) };
		tail.setShape(Type::CIRCLE, (tailLen > 0) ? tailLen : 1 );
		tail.setColor(head.getColor(0), head.getColor(1), head.getColor(2));
	}
}

void Board::swapSnake()
{
	if (field[snake[0].x][snake[0].y].dirSize() != 0)
	{
		Shape& lastTail = field[snake[snake.size() - 1].x][snake[snake.size() - 1].y];
		Direction orgDir = field[snake[0].x][snake[0].y].getDir();
		if (orgDir == Direction::RIGHTDIR)
		{
			lastTail.push(Direction::LEFTDIR);
		}
		else if (orgDir == Direction::LEFTDIR)
		{
			lastTail.push(Direction::RIGHTDIR);
		}
		else if (orgDir == Direction::UPDIR)
		{
			lastTail.push(Direction::DOWNDIR);
		}
		else if (orgDir == Direction::DOWNDIR)
		{
			lastTail.push(Direction::UPDIR);
		}
	}
		

	std::reverse(snake.begin(), snake.end());
	Shape& head = field[snake[0].x][snake[0].y];
	head.setShape(Type::CIRCLE, ws.GetCellLen() / 2);
	applySnakeTiles();
}

void Board::explodeSnake()
{
	POINT p = snake[0];
	for (int i{ 1 }; i < snake.size(); ++i)
	{
		field[snake[i].x][snake[i].y].setShape(Type::NONE);
	}
	snake.clear();
	snake.push_back(p);

	Shape& s = field[snake[0].x][snake[0].y];
	if (s.getType() == Type::TRIANGLE)
	{
		s.setShape(Type::CIRCLE);
	}
	else
	{
		s.setShape(Type::TRIANGLE);
	}
	
}

void Board::seperateSnake(POINT pos)
{
	for (int i{ (int)snake.size() - 1}; i > 0; --i)
	{
		POINT curPos = snake[i];

		Shape& s = field[curPos.x][curPos.y];
		s.setShape(Type::NONE);
		createItem(TileType::MOVER, curPos.x, curPos.y, s.getColor(0), s.getColor(1), s.getColor(1));
		snake.pop_back();

		if (pos.x == curPos.x && pos.y == curPos.y)
			return;
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
	if (checkCollide(headPos, newHead)) return;
	
	// 자기 몸 충돌(이동 금지)
	if (isSnakeAt(newHead))
	{
		field[headPos.x][headPos.y].pop();
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
		Shape& itm = field[newHead.x][newHead.y];
		headBackup.setColor(itm.getColor(0), itm.getColor(1), itm.getColor(2));
		itm.setShape(Type::NONE);
		itm.setTileType(TileType::EMPTY);
		createItem(TileType::MOVER,-1,-1,itm.getColor(0), itm.getColor(1), itm.getColor(2));
	}

	if (ateMover)
	{
		snake.push_back(oldTail);
	}

	// 1) 이동 전 좌표를 전부 지움
	for (const auto& p : prevSnake)
	{
		field[p.x][p.y] = Shape{};
	}

	// 스네이크 헤드 재설정
	field[newHead.x][newHead.y] = headBackup;
	field[newHead.x][newHead.y].setTileType(TileType::PLAYER);

	// dir 큐 소모
	if (field[newHead.x][newHead.y].dirSize() > 1)
	{
		field[newHead.x][newHead.y].pop();
	}
}

void Board::moverMove()
{
	int moveType{};
	std::vector<POINT> movers[6];

	// 이동 타입별로 구분해서 모아두기
	for (int i{}; i < boardRow; ++i)
	{
		for (int j{}; j < boardCol; ++j)
		{
			if (field[i][j].getMoveType() > 0)
			{
				movers[field[i][j].getMoveType()].push_back({i, j});
			}
		}
	}

	// 5 - 1 - 2 - 3 순서로 함
	for (const auto& pt : movers[5])
	{
		int i = pt.x;
		int j = pt.y;

		if (field[i][j].getLength() < ws.GetCellLen())
		{
			field[i][j].setShape(Type::CIRCLE, ws.GetCellLen());
		}
		else
		{
			field[i][j].setShape(Type::CIRCLE, ws.GetCellLen() / 2);
		}
	}
	for (const auto& pt : std::views::reverse(movers[1]))
	{
		int i = pt.x; int j = pt.y;
		Direction dir = field[i][j].getDir();
		const POINT target = nextPos(POINT{ i, j }, dir);

		if (checkCollide(POINT{ i, j }, target) || isSnakeAt(target)
			|| field[target.x][target.x].getTileType() != TileType::EMPTY) continue;
		else
		{
			std::swap(field[i][j], field[target.x][target.y]);
		}
	}
	for (const auto& pt : movers[2])
	{
		int i = pt.x;
		int j = pt.y;

		Direction dir = field[i][j].getDir();
		const POINT target = nextPos(POINT{ i, j }, dir);

		if (checkCollide(POINT{ i, j }, target) || isSnakeAt(target)) continue;
		else
		{
			std::swap(field[i][j], field[target.x][target.y]);
		}
	}
	for (const auto& pt : movers[3])
	{
		int i = pt.x;
		int j = pt.y;

		insertMove3(i, j);

		Direction dir = field[i][j].getDir();
		const POINT target = nextPos(POINT{ i, j }, dir);

		if (checkCollide(POINT{ i, j }, target) || isSnakeAt(target)) continue;
		else
		{
			std::swap(field[i][j], field[target.x][target.y]);
		}
	}
}

void Board::createItem(TileType type, int x, int y, int r, int g, int b)
{
	int dX{ ws.WIDTH / (boardCol * 2) };
	int dY{ ws.HEIGHT / (boardRow * 2) };
	int moveType = uid(gen) % 5 + 1;

	if (x == -1 && y == -1)
	{
		while (true)
		{
			x = uid(gen) % boardCol;
			y = uid(gen) % boardCol;

			if (field[x][y].getTileType() == TileType::EMPTY) break;
		}
	}
	
	if (type == TileType::MOVER)
	{
		field[x][y].setShape(Type::CIRCLE, (dX > dY) ? dY : dX);
		field[x][y].setColor(r, g, b);
		field[x][y].setTileType(TileType::MOVER);

		field[x][y].setMoveType(moveType);
		if (moveType == 1)
		{
			field[x][y].push(Direction::LEFTDIR);
		}
		if (moveType == 2)
		{
			field[x][y].push(Direction::UPDIR);
		}
		if (moveType == 3)
		{
			field[x][y].push(Direction::UPDIR);
		}
		return;
	}
	else if (type == TileType::OBSTACLE)
	{
		field[x][y].setShape(Type::RECTANGLE, (dX > dY) ? dY : dX);
		field[x][y].setColor(r, g, b);
		field[x][y].setTileType(TileType::OBSTACLE);
		return;
	}
}

void Board::insertMove3(int x, int y)
{
	Shape& s = field[x][y];
	Direction dir = s.getDir();

	while (s.dirSize() != 0)
		s.pop();

	if (dir == Direction::LEFTDIR)
	{
		s.push(Direction::UPDIR);
	}
	else if (dir == Direction::RIGHTDIR)
	{
		s.push(Direction::DOWNDIR);
	}
	else if (dir == Direction::UPDIR)
	{
		s.push(Direction::RIGHTDIR);
	}
	else if (dir == Direction::DOWNDIR)
	{
		s.push(Direction::LEFTDIR);
	}
}

void Board::changeDir(Direction dir)
{
	const POINT headPos = snake[0];
	field[headPos.x][headPos.y].push(dir);
}

void Board::setHighSnake()
{
	POINT sPos = snake[0];
	while (sPos.x == 0 && sPos.y == 0)
	{
		// 상하좌우 검사 후 없는 곳으로 가야됨
		
	}
}

void Board::setNormalSnake()
{
}
