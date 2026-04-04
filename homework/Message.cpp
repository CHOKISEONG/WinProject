#include "Message.h"

void Message::OnCreate(HWND hWnd) 
{
    makeBoard();
    setPosition();
}

void Message::OnKeyDown(HWND hWnd, WPARAM wParam)
{
    switch (wParam)
    {
    case VK_UP:case VK_DOWN:case VK_LEFT:case VK_RIGHT:
    case VK_ESCAPE:case VK_BACK:case VK_RETURN:case VK_TAB:
    case VK_HOME:case VK_END:case VK_INSERT:
    case VK_DELETE:case VK_PRIOR:case VK_NEXT:
    case VK_F1:case VK_F2:case VK_F3:case VK_F4:
    case VK_F5:case VK_F6:case VK_F7:case VK_F8:
        KeyHandler::KeyDown(wParam);
        InvalidateRect(hWnd, NULL, TRUE);
        return;
    default:
        break;
    }

    const char key = (char)tolower((int)wParam);

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
