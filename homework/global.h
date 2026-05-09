#pragma once

#include <Windows.h>
#include <chrono>
#include <random>
#include <queue>

constexpr double PI = 3.14159265358979323846;
constexpr double getRadian(double len) { return len * (PI / 180.0); }
float getDistance(POINT p1, POINT p2);

constexpr int WIDTH = 900;
constexpr int HEIGHT = 500;
constexpr int boardRow = 6;
constexpr int boardCol = 6;
constexpr int cell = WIDTH / boardRow;
constexpr int rad = cell / 2;

enum Direction
{
	LEFTDIR,
	RIGHTDIR,
	UPDIR,
	DOWNDIR,
	STOP
};

// 윈도우
class SZ
{
public:
	int width = WIDTH;
	int height = HEIGHT;

	POINT mousePrevPos;
	POINT mousePos;
	POINT mouseDownPos;
	POINT mouseUpPos;
	HWND hWnd = NULL;
	HINSTANCE instance;

	std::vector<RECT> outOfWindowRect;

	// 화면 밖을 체크하는 용도의 RECT 생성
	void makeOOWRect();
};
extern SZ ws;

extern int currentROP2;

extern int TimerFuncFPS;

// 선택한 카드 인덱스
extern int handIdx; 

extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;
