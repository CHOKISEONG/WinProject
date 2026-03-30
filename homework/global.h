#pragma once

#include "header.h"

// 윈도우의 가로, 세로 크기
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

// 메모장의 줄, 글자의 최대
constexpr int MAX_LINE = 10;
constexpr int MAX_LETTER = 30;

// 글자를 입력할 위치
struct Pos { int x, y; };

// 글자 입력의 타입 ( 덮어쓰기, 밀어내기 )
enum LetterType
{
	OVERWRITE,
	PUSH
};

struct PrintType
{
	bool addTapToNum;
	bool putInParentheses;
	bool deleteSpace;
	bool changeToC;
};
extern PrintType printType;

extern TCHAR textBuffer[MAX_LINE][MAX_LETTER + 1];
extern bool isUpper;
extern Pos pos;
extern LetterType type;


// 랜덤값을 구하기 위해
extern std::random_device rd;
extern unsigned __int64 seed;
extern std::mt19937 gen;
extern std::uniform_int_distribution<int> uid;
extern std::uniform_int_distribution<int> uidPos;
extern std::uniform_int_distribution<int> uidColor;

// 함수 선언부
void inputManager(WPARAM& wParam);
void drawPaint(HDC& hDC);
void initialize(HWND& hWnd);
int getLetterLength(int line, TCHAR* textBuff = textBuffer[pos.y], int num = MAX_LETTER);
void addNumberToText(int addNum);
void shiftLine();
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);