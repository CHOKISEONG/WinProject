#include "Message.h"

void Message::OnCreate(HWND hWnd) 
{
    createRect();
    makeTriangle();
    makeRectangle();
    makeCircle();
}

void Message::OnKeyDown(HWND hWnd, WPARAM wParam)
{
    KeyHandler::KeyDown(wParam);
    InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnChar(HWND hWnd, WPARAM wParam) 
{
    KeyHandler::Default(wParam);
}

void Message::OnPaint(HWND hWnd) 
{
    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hWnd, &ps);
    HPEN bkPen, oldPen;
    HBRUSH hBrush, oldBrush;

    bkPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    oldPen = (HPEN)SelectObject(hDC, bkPen);

    // 사각형 1 생성
    hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    FillRect(hDC, &rect1, hBrush);

    // 사각형 2 생성
    hBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    FillRect(hDC, &rect2, hBrush);

    // 도형 생성
    drawTriangle(hDC);
    drawRectangle(hDC, hBrush);
    drawCircle(hDC);

    SelectObject(hDC, oldPen);
    DeleteObject(bkPen);

    EndPaint(hWnd, &ps);
}

void Message::OnSize(HWND hWnd, int width, int height)
{
    ws.WIDTH = width;
    ws.HEIGHT = height;
    InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnDestroy(HWND hWnd)
{
    PostQuitMessage(0);
}
