#include "global.h"

SZ ws;
std::vector<std::vector<Shape>> boards;
std::vector<Shape> board;

std::map<char, bool> isKeyDown{ {'c',false},{'s',false},{'p',false},{'e',false} };

std::random_device rd;
unsigned __int64 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_int_distribution<int> uid(0, 9999);
std::uniform_int_distribution<int> uidColor(0, 255);


void setPosition()
{
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
		}
	}

	// 플레이어 설정
	boards[0][0].tileType = Shape::Player1;
	boards[0][0].type = Shape::SandClock;

	boards[boardCol - 1][0].tileType = Shape::Player2;
	boards[boardCol - 1][0].type = Shape::Pentagon;

	// 골 설정
	boards[boardCol / 2][boardRow - 1].tileType = Shape::Goal;
	int rand = uid(gen) % 4;
	if (rand == 0) boards[boardCol / 2][boardRow - 1].type = Shape::Triangle;
	else if (rand == 1) boards[boardCol / 2][boardRow - 1].type = Shape::Pie;
	else if (rand == 2) boards[boardCol / 2][boardRow - 1].type = Shape::Cirle;
	else if (rand == 3) boards[boardCol / 2][boardRow - 1].type = Shape::Star;
	boards[boardCol / 2][boardRow - 1].setColor(uidColor(gen), uidColor(gen), uidColor(gen));

	// 특수칸 설정
	makeTile(Shape::Obstacle	, uid(gen) % 5 + 30);
	makeTile(Shape::Resize		, uid(gen) % 5 + 10);
	makeTile(Shape::ReShape		, uid(gen) % 5 + 10);
	makeTile(Shape::ChangeColor	, uid(gen) % 5 + 10);
}

void makeTile(Shape::TileType type, const int tileNum)
{
	int col{}, row{};
	for (int i{}; i < tileNum; ++i)
	{
		while (true)
		{
			col = uid(gen) % boardCol;
			row = uid(gen) % boardRow;

			if (boards[col][row].tileType == Shape::TileType::Nothing) break;
		}

		boards[col][row].tileType = type;

		// 색깔 설정
		if (type == Shape::ChangeColor && uid(gen) % 2)
		{
			boards[col][row].color = boards[boardCol / 2][boardRow - 1].color;
		}
		else if (type == Shape::Obstacle)
		{
			boards[col][row].setColor(255, 0, 0);
		}
		else
		{
			boards[col][row].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
		}

		// 도형 설정
		if (type == Shape::Obstacle || type == Shape::Resize || type == Shape::TileType::ChangeColor)
			boards[col][row].type = Shape::Rect;
		else if (type == Shape::ReShape)
		{
			int rand = uid(gen) % 4;
			if (rand == 0) boards[col][row].type = Shape::Triangle;
			else if (rand == 1) boards[col][row].type = Shape::Pie;
			else if (rand == 2) boards[col][row].type = Shape::Cirle;
			else if (rand == 3) boards[col][row].type = Shape::Star;
		}

		// ReSize의 경우 숫자 설정
		if (type == Shape::Resize)
		{
			boards[col][row].resizeNum = uid(gen) % 7 - 3;
		}
	}
}

void makePolygons()
{
	const int cellW = ws.WIDTH / boardCol;
	const int cellH = ws.HEIGHT / boardRow;
	const int halfW = cellW / 2;
	const int halfH = cellH / 2;
	const int length = ws.GetLength();

	for (auto& b : boards)
	{
		for (auto& s : b)
		{
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

	for (const auto& b : boards)
	{
		for (const auto& s : b)
		{
			if (s.type == Shape::Type::None) continue;

			hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			hBrush = CreateSolidBrush(RGB(s.color.r, s.color.g, s.color.b));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			std::vector<POINT> p{};
			p.resize(s.pointNum);
			for (int i{}; i < s.pointNum; ++i)
			{
				p[i].x = s.point[i].x + s.position.x;
				p[i].y = s.point[i].y + s.position.y;
			}

			if (s.type == Shape::Cirle || s.type == Shape::Ellipse)
			{
				Ellipse(hDC, p[0].x, p[0].y, p[1].x, p[1].y);
			}
			else if (s.type == Shape::SandClock)
			{
				Polygon(hDC, p.data(), 5);
			}
			else if (s.type == Shape::Triangle 
					|| s.type == Shape::Rect
					|| s.type == Shape::Pentagon
					|| s.type == Shape::Star)
			{
				Polygon(hDC, p.data(), p.size());
			}
			else if (s.type == Shape::Pie)
			{
				Pie(hDC, p[0].x, p[0].y, p[1].x, p[1].y, p[3].x, p[3].y, p[2].x, p[2].y);
			}

			// 숫자 띄우기
			if (s.tileType == Shape::Resize)
			{
				const std::wstring text = std::to_wstring(s.resizeNum);

				RECT rc{};

				rc.left = p[0].x;
				rc.top = p[0].y;
				rc.right = p[2].x;
				rc.bottom = p[2].y;

				const int oldBkMode = SetBkMode(hDC, TRANSPARENT);
				const COLORREF oldTextColor = SetTextColor(hDC, RGB(0, 0, 0));

				DrawTextW(
					hDC,
					text.c_str(),
					-1,
					&rc,
					DT_CENTER | DT_VCENTER | DT_SINGLELINE
				);

				SetTextColor(hDC, oldTextColor);
				SetBkMode(hDC, oldBkMode);
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
