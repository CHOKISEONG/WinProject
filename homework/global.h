#pragma once

#include "header.h"

constexpr double PI = 3.14159265358979323846;
constexpr double getRadian(double len) { return len * (PI / 180.0); }

constexpr int boardRow = 40;
constexpr int boardCol = 40;

// 윈도우
class SZ
{
public:
	int WIDTH = 1200;
	int HEIGHT = 800;

	POINT mouse;

	int GetCellLen() const
	{
		return (WIDTH > HEIGHT) ? WIDTH / boardCol : HEIGHT / boardRow;
	}

	HWND hWnd = NULL;
};
extern SZ ws;

extern int currentROP2;

extern bool isAkeyToggled;

extern bool rButtonClicked;

extern int playerAnimEvent;
extern int playerAnimFPS;
extern int timerProcCnt;

extern bool isGameStarted;

// 랜덤값을 구하기 위해
extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;
