#include "Message.h"

void Message::OnCreate(HWND hWnd) 
{
    setPosition();
    makePolygons();
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
    
    drawPolygons(hDC);

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
