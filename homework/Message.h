#pragma once
#include "global.h"

class Message 
{
public:
    // 윈도우가 생성될 때
    static void OnCreate(HWND hWnd);

    // 특수키 처리용
    static void OnKeyDown(HWND hWnd, WPARAM wParam);

    static void OnKeyUp(HWND hWnd, WPARAM wParam);

    // 문자를 눌렀을 때
    static void OnChar(HWND hWnd, WPARAM wParam);

    // 그리기가 호출되었을 때
    static void OnPaint(HWND hWnd);

    // 윈도우가 종료될 때
    static void OnDestroy(HWND hWnd);

    // 윈도우 크기가 변경될 때
    static void OnSize(HWND hWnd, int width, int height);

    // 마우스가 움직일 때
    static void MouseMove(int mouse_x, int mouse_y);

    static void LMouseClick();
    static void RMouseClick();
    static void LMouseDBClick();
    static void RMouseDBClick();

    static void SnakeTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);
    static void MoverTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);
};