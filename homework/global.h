#pragma once

#include "header.h"
#include "Shape.h"

constexpr double PI = 3.14159265358979323846;
constexpr double getRadian(double len) { return len * (PI / 180.0); }
float getDistance(int x1, int y1, int x2, int y2);

// 윈도우
class SZ
{
public:
	int WIDTH = 1200;
	int HEIGHT = 800;

	POINT mouse;

	int GetLength() const
	{
		return (WIDTH > HEIGHT) ? WIDTH / 80 : HEIGHT / 80;
	}

	HWND hWnd = NULL;
};
extern SZ ws;

// 색깔
struct Color { unsigned int r, g, b; };

extern int currentROP2;

extern bool rButtonClicked;

// 랜덤값을 구하기 위해
extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;
