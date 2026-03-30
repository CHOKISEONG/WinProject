#pragma once

#include "global.h"

class KeyHandler
{
public:
	// 입력한 키를 해당하는 함수로 연결
	static void KeyDown(WPARAM wParam);

	// 일반적인 키들은 여기로
	static void Default(WPARAM key);

	// 특수키들은 여기로
	static void Enter();
	static void BackSpace();
	static void Esc();
	static void Arrow(WPARAM wParam);
	static void Tab();
	static void Home();
	static void End();
	static void Insert();
	static void Del();
	static void PgUp();
	static void PgDown();
	static void F1();
	static void F2();
	static void F3();
	static void F4();
	static void F5();
	static void F6();
	static void F7();
	static void F8();
};