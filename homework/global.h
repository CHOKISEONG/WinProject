#pragma once

#include "header.h"

constexpr double PI = 3.14159265358979323846;
constexpr double getRadian(double len) { return len * (PI / 180.0); }
inline bool IsColliding(const RECT& a, const RECT& b) 
{
	return (a.left < b.right && a.right > b.left && a.top < b.bottom && a.bottom > b.top);
}
extern float getDistance(POINT p1, POINT p2);


// À©µµ¿ì
class SZ
{
public:
	int WIDTH = 800;
	int HEIGHT = 600;

	POINT mousePos;
	HWND hWnd = NULL;
};
extern SZ ws;

enum class TrafficSignal
{
	RED,
	YELLOW,
	GREEN,
	RED_ALL
};

extern std::map<char, bool> isKeyDown;

extern int currentROP2;

extern int TimerFuncFPS;
extern float deltaTime;

extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;
