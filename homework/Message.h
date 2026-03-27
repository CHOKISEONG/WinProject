#pragma once
#include "global.h"

class Message {
public:
    // 윈도우가 생성될 때
    static void OnCreate(HWND hWnd);

    // 특수키 처리용
    static void OnKeyDown(HWND hWnd, WPARAM wParam);

    // 문자를 눌렀을 때
    static void OnChar(HWND hWnd, WPARAM wParam);

    // 그리기가 호출되었을 때
    static void OnPaint(HWND hWnd);

    // 윈도우가 종료될 때
    static void OnDestroy(HWND hWnd);
};