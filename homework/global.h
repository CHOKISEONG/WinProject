#pragma once

#include "header.h"

// 윈도우의 가로, 세로 크기
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

constexpr int LENGTH = 5;

// 색깔
struct Color { unsigned int r, g,  b; };

extern RECT rect1, rect2;
extern LPRECT rect3;
extern POINT point;
extern unsigned int rect1Color, rect2Color;
extern Color triColor, rectColor, circleColor;

// 랜덤값을 구하기 위해
extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidColor;

// 함수 선언부
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void createRect();
void drawTriangle(HDC hDC);
void drawRectangle(HDC hDC, HBRUSH& brush);
void drawCircle(HDC hDC);