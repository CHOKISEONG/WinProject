#include "global.h"

SZ ws;
std::vector<Shape> shapes;
int midShapeIdx;
std::vector<Shape> board;

std::map<char, bool> isKeyDown{ {'c',false},{'s',false},{'p',false},{'e',false} };

std::random_device rd;
unsigned __int64 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_int_distribution<int> uid(0, 9999);
std::uniform_int_distribution<int> uidColor(0, 255);


void setPosition()
{
	
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

	for (const auto& s : shapes)
	{
		hPen = CreatePen(PS_SOLID, 3, RGB(255 - s.color.r, 255 - s.color.g, 255 - s.color.b));
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

		if (s.type == Shape::Cirle)
		{
			Ellipse(hDC, p[0].x, p[0].y, p[1].x, p[1].y);
		}
		else if (s.type == Shape::SandClock)
		{
			Polygon(hDC, p.data(), 5);
		}
		else if (s.type == Shape::Pentagon)
		{
			Polygon(hDC, p.data(), 5);
		}
		else if (s.type == Shape::Pie)
		{
			Pie(hDC, p[0].x, p[0].y, p[1].x, p[1].y, p[3].x, p[3].y, p[2].x, p[2].y);
		}

		SelectObject(hDC, oldPen);
		DeleteObject(hPen);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
	}
}

void drawBoard(HDC hDC)
{
	HPEN hPen, oldPen;

	hPen = CreatePen(PS_DASHDOT, 4, RGB(0,0,0));
	oldPen = (HPEN)SelectObject(hDC, hPen);

	for (int i{}; i < board.size(); ++ i)
	{
		Polygon(hDC, board[i].point, 2);
	}

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);
}

void makePolygons()
{
	for (auto& s : shapes)
	{
		s.color.r = uidColor(gen);
		s.color.g = uidColor(gen);
		s.color.b = uidColor(gen);

		const int length = ws.GetLength();

		if (s.type == Shape::Cirle)
		{
			s.point = new POINT[2];
			s.point[0].x = -length;
			s.point[0].y = -length;
			s.point[1].x =  length;
			s.point[1].y =  length;

			s.pointNum = 2;
		}
		else if (s.type == Shape::SandClock)
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
		else if (s.type == Shape::Pentagon)
		{
			s.point = new POINT[5];

			for (int i{}; i < 5; ++i)
			{
				s.point[i].x = cos(getRadian(i * 72.0f)) * length;
				s.point[i].y = sin(getRadian(i * 72.0f)) * length;
			}

			s.pointNum = 5;
		}
		else if (s.type == Shape::Pie)
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
	}
}

void shapeSwap(Shape& a, Shape& b)
{
	POINT aPos = a.position, bPos = b.position;

	std::swap(a, b);

	a.position = aPos;
	b.position = bPos;
}
