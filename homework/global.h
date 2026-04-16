#pragma once

#include "header.h"

constexpr double PI = 3.14159265358979323846;
constexpr double getRadian(double len) { return len * (PI / 180.0); }
extern float getDistance(POINT p1, POINT p2);

// À©µµ¿ì
class SZ
{
public:
	int WIDTH = 1200;
	int HEIGHT = 800;

	POINT mousePos;
	HWND hWnd = NULL;
};
extern SZ ws;

enum class TrafficSignal
{
	RED,
	YELLOW,
	GREEN
};

extern int currentROP2;

extern int TimerFuncFPS;
extern float deltaTime;

extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;
