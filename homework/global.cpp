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

	// 플레이어 설정
	boards[0][0].tileType = Shape::Player1;
	boards[0][0].type = (uid(gen) % 2) ?  Shape::Pentagon : Shape::SandClock;
	boards[0][0].setColor(uidColor(gen), uidColor(gen), uidColor(gen));

	boards[boardCol - 1][0].tileType = Shape::Player2;
	boards[boardCol - 1][0].type = (uid(gen) % 2 == 1) ? Shape::Pentagon : Shape::SandClock;
	boards[boardCol - 1][0].setColor(uidColor(gen), uidColor(gen), uidColor(gen));

	// 골 설정
	boards[boardCol / 2][boardRow - 1].tileType = Shape::Goal;
	int rand = uid(gen) % 4;
	if (rand == 0) boards[boardCol / 2][boardRow - 1].type = Shape::Triangle;
	else if (rand == 1) boards[boardCol / 2][boardRow - 1].type = Shape::Pie;
	else if (rand == 2) boards[boardCol / 2][boardRow - 1].type = Shape::Cirle;
	else if (rand == 3) boards[boardCol / 2][boardRow - 1].type = Shape::Star;
	boards[boardCol / 2][boardRow - 1].setColor(uidColor(gen), uidColor(gen), uidColor(gen));
	boards[boardCol / 2][boardRow - 1].resizeNum = uid(gen) % 7 - 3;

	// 특수칸 설정
	makeTile(Shape::Obstacle, uid(gen) % 5 + 30);
	makeTile(Shape::Resize, uid(gen) % 5 + 10);
	makeTile(Shape::ReShape, uid(gen) % 5 + 10);
	makeTile(Shape::ChangeColor, uid(gen) % 5 + 10);

	makePolygons();
}

void makeTile(Shape::TileType type, const int tileNum)
{
	std::vector<POINT> emptyCells{};
	emptyCells.reserve(boardCol * boardRow);

	for (int col{}; col < boardCol; ++col)
	{
		for (int row{}; row < boardRow; ++row)
		{
			if (boards[col][row].tileType == Shape::TileType::Nothing)
			{
				emptyCells.push_back(POINT{ col, row });
			}
		}
	}

	if (emptyCells.empty())
	{
		return;
	}

	std::shuffle(emptyCells.begin(), emptyCells.end(), gen);

	const int placeCount = (tileNum < (int)emptyCells.size()) ? tileNum : (int)emptyCells.size();

	for (int i{}; i < placeCount; ++i)
	{
		const int col = emptyCells[i].x;
		const int row = emptyCells[i].y;

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
		{
			boards[col][row].type = Shape::Rect;
		}
		else if (type == Shape::ReShape)
		{
			const int rand = uid(gen) % 4;
			if (rand == 0) boards[col][row].type = Shape::Triangle;
			else if (rand == 1) boards[col][row].type = Shape::Pie;
			else if (rand == 2) boards[col][row].type = Shape::Cirle;
			else if (rand == 3) boards[col][row].type = Shape::Star;

			boards[col][row].reShapeCnt = 3;
		}

		// ReSize의 경우 숫자 설정
		if (type == Shape::Resize)
		{
			boards[col][row].resizeNum = uid(gen) % 7 - 3;
		}
	}
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
			float resized{1.0f};
			switch (s.resizeNum)
			{
			case -3:
				resized = 0.5f;
				break;
			case -2:
				resized = 0.7f;
				break;
			case -1:
				resized = 0.9f;
				break;
			case 1:
				resized = 1.1f;
				break;
			case 2:
				resized = 1.3f;
				break;
			case 3:
				resized = 1.5f;
				break;
			default:
				break;
			}

			for (int i{}; i < s.pointNum; ++i)
			{
				p[i].x = s.point[i].x * resized + s.position.x;
				p[i].y = s.point[i].y * resized + s.position.y;
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
			if (s.resizeNum != 0)
			{
				const std::wstring text = std::to_wstring(s.resizeNum);

				RECT rc{};

				if (s.type == Shape::Cirle || s.type == Shape::Ellipse)
				{
					rc.left = min(p[0].x, p[1].x);
					rc.top = min(p[0].y, p[1].y);
					rc.right = max(p[0].x, p[1].x);
					rc.bottom = max(p[0].y, p[1].y);
				}
				else
				{
					int left = p[0].x, right = p[0].x;
					int top = p[0].y, bottom = p[0].y;

					for (int i{}; i < (int)p.size(); ++i)
					{
						left = min(left, p[i].x);
						right = max(right, p[i].x);
						top = min(top, p[i].y);
						bottom = max(bottom, p[i].y);
					}

					rc.left = left;
					rc.top = top;
					rc.right = right;
					rc.bottom = bottom;
				}

				const int oldBkMode = SetBkMode(hDC, TRANSPARENT);
				const COLORREF oldTextColor = SetTextColor(hDC, RGB(0, 0, 0));

				DrawTextW(hDC, text.c_str(), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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

void moveTile(POINT pos, POINT target)
{
	Shape& targetCell = boards[target.x][target.y];
	const Shape::TileType tileType = targetCell.tileType;

	if (tileType == Shape::Obstacle || tileType == Shape::Player1 || tileType == Shape::Player2)
	{
		return;
	}

	if (tileType == Shape::Goal)
	{
		checkWin(pos, target);
		return;
	}

	const Shape::Type savedType = targetCell.type;
	const Color savedColor = targetCell.color;
	const int savedResizeNum = targetCell.resizeNum;
	const int savedReShapeCnt = targetCell.reShapeCnt;

	shapeSwap(boards[pos.x][pos.y], boards[target.x][target.y]);

	Shape& mover = boards[target.x][target.y];

	switch (tileType)
	{
	case Shape::Resize:
		mover.resizeNum = savedResizeNum;
		break;

	case Shape::ChangeColor:
		mover.color = savedColor;
		break;

	case Shape::ReShape:
		mover.type = savedType;
		mover.reShapeCnt = savedReShapeCnt;
		applyPolygon(target.x, target.y);
		break;

	default:
		break;
	}

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

void checkWin(POINT pos, POINT target)
{
	if (boards[pos.x][pos.y].type == boards[target.x][target.y].type
		&& boards[pos.x][pos.y].resizeNum == boards[target.x][target.y].resizeNum
		&& boards[pos.x][pos.y].color.r == boards[target.x][target.y].color.r
		&& boards[pos.x][pos.y].color.g == boards[target.x][target.y].color.g
		&& boards[pos.x][pos.y].color.b == boards[target.x][target.y].color.b)
	{
		const wchar_t* text = (boards[pos.x][pos.y].tileType == Shape::Player1)
			? L"Player1 Win!!! Congratulations!"
			: L"Player2 Win!!! Congratulations!";

		MessageBoxW(ws.hWnd, text, L"Game Over", MB_OK | MB_ICONINFORMATION);
		PostQuitMessage(0);
	}
}
