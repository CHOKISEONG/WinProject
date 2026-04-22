#pragma once
#include "global.h"

class Message 
{
public:
    // 윈도우가 생성될 때
    static void OnCreate(HWND hWnd);

    // 키보드 처리
    static void OnKeyDown(HWND hWnd, WPARAM wParam);
    static void OnKeyUp(HWND hWnd, WPARAM wParam);
    static void OnChar(HWND hWnd, WPARAM wParam);

    // 그리기가 호출되었을 때
    static void OnPaint(HWND hWnd);

    // 윈도우가 종료될 때
    static void OnDestroy(HWND hWnd);

    // 윈도우 크기가 변경될 때
    static void OnSize(HWND hWnd, int width, int height);

    static void OnMessage(HWND hWnd, WPARAM wParam);

    // 마우스가 움직일 때
    static void MouseMove(int mouse_x, int mouse_y);

    static void LMouseClick();
    static void RMouseClick();
    static void LMouseDBClick();
    static void RMouseDBClick();

    static void TimerFunc(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);
};