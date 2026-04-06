#include "global.h"

SZ ws;
std::vector<std::vector<Shape>> boards;
std::vector<Shape> board;
int whosTurn = 1;

std::map<char, bool> isKeyDown{ {'c',false},{'s',false},{'p',false},{'e',false} };

std::random_device rd;
unsigned __int64 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_int_distribution<int> uid(0, 9999);
std::uniform_int_distribution<int> uidColor(0, 255);


void setPosition()
{
	for (auto& col : boards)
	{
		for (auto& cell : col)
		{
			if (cell.point != nullptr)
			{
				delete[] cell.point;
				cell.point = nullptr;
				cell.pointNum = 0;
			}
		}
	}

	boards.clear();
	boards.resize(boardCol);
	for (int i{}; i < boardCol; ++i)
	{
		boards[i].clear();
		boards[i].resize(boardRow);
	}

	const int cellW = ws.WIDTH / boardCol;
	const int cellH = ws.HEIGHT / boardRow;
	const int halfW = cellW / 2;
	const int halfH = cellH / 2;

	for (int i{}; i < boardCol; ++i)
	{
		for (int j{}; j < boardRow; ++j)
		{
			boards[i][j].type = Shape::Type::None;
			boards[i][j].tileType = Shape::TileType::Nothing;

			boards[i][j].position.x = i * cellW + halfW;
			boards[i][j].position.y = j * cellH + halfH;

			boards[i][j].point = nullptr;
			boards[i][j].pointNum = 0;
			boards[i][j].resizeNum = 0;
			boards[i][j].reShapeCnt = 0;
		}
	}

	makePolygons();
}

POINT getTile(Shape::TileType type)
{
	for (int i{}; i < boardCol; ++i)
	{
		for (int j{}; j < boardRow; ++j)
		{
			if (boards[i][j].tileType == type)
			{
				return POINT(i, j);
			}
		}
	}
	return POINT();
}

void applyPolygon(int col, int row)
{
	if (col < 0 || col >= boardCol || row < 0 || row >= boardRow)
	{
		return;
	}

	Shape& s = boards[col][row];


	if (s.point != nullptr)
	{
		delete[] s.point;
		s.point = nullptr;
		s.pointNum = 0;
	}

	const int cellW = ws.WIDTH / boardCol;
	const int cellH = ws.HEIGHT / boardRow;
	const int halfW = cellW / 2;
	const int halfH = cellH / 2;
	const int length = ws.GetLength();

	Shape::Type type = s.type;
	if (type == Shape::Cirle)
	{
		s.point = new POINT[2];
		s.point[0].x = -length;
		s.point[0].y = -length;
		s.point[1].x = length;
		s.point[1].y = length;

		s.pointNum = 2;
	}
	else if (type == Shape::Ellipse)
	{
		s.point = new POINT[2];
		s.point[0].x = -length;
		s.point[0].y = -length * 0.8f;
		s.point[1].x = length;
		s.point[1].y = length * 0.8f;

		s.pointNum = 2;
	}
	else if (type == Shape::SandClock)
	{
		s.point = new POINT[5];
		s.point[0].x = -length;
		s.point[0].y = -length;

		s.point[1].x = +length;
		s.point[1].y = -length;

		s.point[2].x = -length;
		s.point[2].y = +length;

		s.point[3].x = +length;
		s.point[3].y = +length;

		s.point[4].x = -length;
		s.point[4].y = -length;

		s.pointNum = 5;
	}
	else if (type == Shape::Triangle)
	{
		s.point = new POINT[3];

		for (int i{}; i < 3; ++i)
		{
			s.point[i].x = cos(getRadian(i * 120.0f)) * length;
			s.point[i].y = sin(getRadian(i * 120.0f)) * length;
		}

		s.pointNum = 3;
	}
	else if (type == Shape::Rect)
	{
		s.point = new POINT[4];

		s.point[0] = { -halfW, -halfH };
		s.point[1] = { +halfW, -halfH };
		s.point[2] = { +halfW, +halfH };
		s.point[3] = { -halfW, +halfH };

		s.pointNum = 4;
	}
	else if (type == Shape::Pentagon)
	{
		s.point = new POINT[5];

		for (int i{}; i < 5; ++i)
		{
			s.point[i].x = cos(getRadian(i * 72.0f)) * length;
			s.point[i].y = sin(getRadian(i * 72.0f)) * length;
		}

		s.pointNum = 5;
	}
	else if (type == Shape::Pie)
	{
		s.point = new POINT[4];
		s.point[0].x = -length;
		s.point[0].y = -length;

		s.point[1].x = length;
		s.point[1].y = length;

		s.point[2].x = 0;
		s.point[2].y = -length;

		s.point[3].x = -length;
		s.point[3].y = 0;

		s.pointNum = 4;
	}
	else if (type == Shape::Star)
	{
		s.point = new POINT[10];

		for (int i{}; i < 10; ++i)
		{
			if (i % 2)
			{
				s.point[i].x = cos(getRadian(i * 36.0f)) * length / 2;
				s.point[i].y = sin(getRadian(i * 36.0f)) * length / 2;
			}
			else
			{
				s.point[i].x = cos(getRadian(i * 36.0f)) * length;
				s.point[i].y = sin(getRadian(i * 36.0f)) * length;
			}
		}

		s.pointNum = 10;
	}
	else
	{
		s.point = nullptr;
		s.pointNum = 0;
	}
}

void makePolygons()
{
	for (int col{}; col < boardCol; ++col)
	{
		for (int row{}; row < boardRow; ++row)
		{
			applyPolygon(col, row);
		}
	}
}

void makeBoard()
{
	board.clear();
	board.resize(boardRow + boardCol);

	int idx{};
	for (int i{}; i < boardRow; ++i)
	{
		board[idx].point = new POINT[2];

		board[idx].point[0].x = 0;
		board[idx].point[0].y = ws.HEIGHT * i / boardRow;
		board[idx].point[1].x = ws.WIDTH;
		board[idx].point[1].y = ws.HEIGHT * i / boardRow;

		++idx;
	}

	for (int i{}; i < boardCol; ++i)
	{
		board[idx].point = new POINT[2];

		board[idx].point[0].x = ws.WIDTH * i / boardCol;
		board[idx].point[0].y = 0;
		board[idx].point[1].x = ws.WIDTH * i / boardCol;;
		board[idx].point[1].y = ws.HEIGHT;

		++idx;
	}
}

void drawPolygons(HDC hDC)
{
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	Shape* selectedCell = nullptr;
	if (choicedNum >= 0 && choicedNum < (int)p.size())
	{
		selectedCell = &boards[p[choicedNum].x][p[choicedNum].y];
	}

	for (const auto& b : boards)
	{
		for (const auto& s : b)
		{
			if (s.type == Shape::Type::None) continue;

			const bool isSelected = (selectedCell != nullptr && &s == selectedCell);

			hPen = CreatePen(PS_SOLID, isSelected ? 200 : 1, RGB(0, 0, 0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			hBrush = CreateSolidBrush(RGB(s.color.r, s.color.g, s.color.b));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			std::vector<POINT> drawPoints{};
			drawPoints.resize(s.pointNum);

			float resized{ 1.0f };
			switch (s.resizeNum)
			{
			case -3: resized = 0.5f; break;
			case -2: resized = 0.7f; break;
			case -1: resized = 0.9f; break;
			case 1: resized = 1.1f; break;
			case 2: resized = 1.3f; break;
			case 3: resized = 1.5f; break;
			default: break;
			}

			for (int i{}; i < s.pointNum; ++i)
			{
				drawPoints[i].x = (LONG)(s.point[i].x * resized + s.position.x);
				drawPoints[i].y = (LONG)(s.point[i].y * resized + s.position.y);
			}

			if (s.type == Shape::Cirle || s.type == Shape::Ellipse)
			{
				Ellipse(hDC, drawPoints[0].x, drawPoints[0].y, drawPoints[1].x, drawPoints[1].y);
			}
			else if (s.type == Shape::SandClock)
			{
				Polygon(hDC, drawPoints.data(), 5);
			}
			else if (s.type == Shape::Triangle
				|| s.type == Shape::Rect
				|| s.type == Shape::Pentagon
				|| s.type == Shape::Star)
			{
				Polygon(hDC, drawPoints.data(), (int)drawPoints.size());
			}
			else if (s.type == Shape::Pie)
			{
				Pie(hDC, drawPoints[0].x, drawPoints[0].y, drawPoints[1].x, drawPoints[1].y, drawPoints[3].x, drawPoints[3].y, drawPoints[2].x, drawPoints[2].y);
			}

			SelectObject(hDC, oldPen);
			DeleteObject(hPen);

			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
		}
	}
}

void drawBoard(HDC hDC)
{
	HPEN hPen, oldPen;

	hPen = CreatePen(PS_DASHDOT, 2, RGB(0,0,0));
	oldPen = (HPEN)SelectObject(hDC, hPen);

	for (int i{}; i < board.size(); ++ i)
	{
		Polygon(hDC, board[i].point, 2);
	}

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);
}

void shapeSwap(Shape& a, Shape& b)
{
	POINT aPos = a.position, bPos = b.position;

	std::swap(a, b);

	a.position = aPos;
	b.position = bPos;
}

void moveTile(POINT pos, POINT target)
{
	Shape& targetCell = boards[target.x][target.y];
	const Shape::TileType tileType = targetCell.tileType;

	const Shape::Type savedType = targetCell.type;
	const Color savedColor = targetCell.color;
	const int savedResizeNum = targetCell.resizeNum;
	const int savedReShapeCnt = targetCell.reShapeCnt;

	shapeSwap(boards[pos.x][pos.y], boards[target.x][target.y]);

	Shape& steppedCell = boards[pos.x][pos.y];

	if (steppedCell.point != nullptr)
	{
		delete[] steppedCell.point;
		steppedCell.point = nullptr;
		steppedCell.pointNum = 0;
	}

	steppedCell.type = Shape::None;
	steppedCell.tileType = Shape::Nothing;
	steppedCell.resizeNum = 0;
	steppedCell.reShapeCnt = 0;
}

POINT getEmptyTile()
{
	POINT p;

	while (true)
	{
		p.x = uid(gen) % boardCol;
		p.y = uid(gen) % boardRow;

		if (boards[p.x][p.y].type == Shape::None)
			return p;
	}
}
