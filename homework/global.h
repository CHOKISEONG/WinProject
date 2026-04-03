#pragma once

#include "header.h"

// 윈도우의 가로, 세로 크기
class SZ
{
public:
	int WIDTH = 800;
	int HEIGHT = 600;

	int LENGTH = (WIDTH > HEIGHT) ? WIDTH / 6 : HEIGHT / 6;
};
extern SZ ws;

// 색깔
struct Color { unsigned int r, g,  b; };


extern std::vector<POINT*> triangles, rects, circles;

// 랜덤값을 구하기 위해
extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;

// 함수 선언부
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
