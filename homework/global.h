#pragma once

#include "header.h"

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

	HWND hWnd = NULL;
};
extern SZ ws;

// 색깔
struct Color { unsigned int r, g, b; };

extern std::string str;

// 랜덤값을 구하기 위해
extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;
