#include "Message.h"

void Message::OnCreate(HWND hWnd) 
{
    makeBoard();
    setPosition();
    makePolygons();
}

void Message::OnKeyDown(HWND hWnd, WPARAM wParam)
{
    const char key = (char)tolower(wParam);

    if (!isKeyDown[key])
    {
        isKeyDown[key] = true;
        KeyHandler::KeyDown(wParam);
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void Message::OnKeyUp(HWND hWnd, WPARAM wParam)
{
    const char key = (char)tolower((int)wParam);
    isKeyDown[key] = false;
    InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnChar(HWND hWnd, WPARAM wParam) 
{
    InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnPaint(HWND hWnd) 
{
    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(hWnd, &ps);
    
    drawBoard(hDC);
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
