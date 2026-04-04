#pragma once

#include "header.h"

constexpr int boardRow = 40;
constexpr int boardCol = 40;

constexpr double PI = 3.14159265358979323846;
constexpr double getRadian(double len) { return len * (PI / 180.0); }

// 윈도우의 가로, 세로 크기
class SZ
{
public:
	int WIDTH = 1200;
	int HEIGHT = 800;

	int GetLength() const
	{
		return (WIDTH > HEIGHT) ? WIDTH / 80 : HEIGHT / 80;
	}
};
extern SZ ws;

// 색깔
struct Color { unsigned int r, g,  b; };

struct Shape
{
	POINT position;
	POINT* point;
	Color color, tmpColor;
	int pointNum;
	
	int resizeNum;

	// 그려지는 도형의 타입
	enum Type
	{
		None,
		Triangle,
		Ellipse,
		Cirle,
		SandClock,
		Pentagon,
		Pie,
		Rect,
		Star
	} type;

	// 타일의 속성
	enum TileType
	{
		Nothing,
		Player1,
		Player2,
		Obstacle,
		ReShape,
		Resize,
		ChangeColor,
		Goal
	} tileType;

	void setColor(float r, float g, float b) { color.r = r; color.g = g; color.b = b; }
};

extern std::vector<std::vector<Shape>> boards;
extern std::vector<Shape> board;

extern std::map<char, bool> isKeyDown;

// 랜덤값을 구하기 위해
extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;

// 함수 선언부
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void setPosition();
void makeBoard();
void makePolygons();
void makeTile(Shape::TileType type, const int tileNum = 0);

void drawPolygons(HDC hDC);
void drawBoard(HDC hDC);

void shapeSwap(Shape& a, Shape& b);