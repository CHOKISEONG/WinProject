#include "Message.h"

void Message::OnCreate(HWND hWnd) 
{
    createRect();
    rect1Color = uidColor(gen);
    rect2Color = uidColor(gen);

    triColor.r = uidColor(gen);
    triColor.g = uidColor(gen);
    triColor.b = uidColor(gen);

    rectColor.r = uidColor(gen);
    rectColor.g = uidColor(gen);
    rectColor.b = uidColor(gen);

    circleColor.r = uidColor(gen);
    circleColor.g = uidColor(gen);
    circleColor.b = uidColor(gen);
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

    hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    FillRect(hDC, &rect1, hBrush);

    hBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    FillRect(hDC, &rect2, hBrush);

    // BOOL PtInRect(CONST RECT * lprc, POINT pt); –특정좌표pt가lprc영역안에있는지검사한다
    hBrush = CreateSolidBrush(RGB(triColor.r, triColor.g, triColor.b));
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    drawTriangle(hDC);

    SelectObject(hDC, oldBrush);
    DeleteObject(hBrush);

    hBrush = CreateSolidBrush(RGB(rectColor.r, rectColor.g, rectColor.b));
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    drawRectangle(hDC, hBrush);

    SelectObject(hDC, oldBrush);
    DeleteObject(hBrush);

    hBrush = CreateSolidBrush(RGB(circleColor.r, circleColor.g, circleColor.b));
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    drawCircle(hDC);

    SelectObject(hDC, oldBrush);
    DeleteObject(hBrush);

    SelectObject(hDC, oldPen);
    DeleteObject(bkPen);

    EndPaint(hWnd, &ps);
}

void Message::OnDestroy(HWND hWnd)
{
    PostQuitMessage(0);
}
