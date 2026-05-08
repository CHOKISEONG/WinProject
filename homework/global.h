#pragma once

#include "header.h"

constexpr double PI = 3.14159265358979323846;
constexpr double getRadian(double len) { return len * (PI / 180.0); }
float getDistance(POINT p1, POINT p2);

constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;
constexpr int boardRow = 10;
constexpr int boardCol = 10;
constexpr int cell = WIDTH / boardRow;
constexpr int rad = cell / 2;

// À©µµ¿ì
class SZ
{
public:
	int width = WIDTH;
	int height = HEIGHT;

	POINT mousePos;
	HWND hWnd = NULL;
	HINSTANCE instance;
};
extern SZ ws;

extern int currentROP2;

extern int TimerFuncFPS;

extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;
