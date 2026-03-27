#include "Message.h"

void Message::OnCreate(HWND hWnd) 
{
    pos.x = 0;
    pos.y = 0;
    CreateCaret(hWnd, NULL, 3, 15);
    ShowCaret(hWnd);
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

    SIZE size{};

    for (int i{}; i < MAX_LINE; ++i)
    {
        int letterCnt = checkLetterCnt(i);

        if (letterCnt != 0)
        {
            GetTextExtentPoint32W(hDC, textBuffer[i], letterCnt, &size);
            TextOutW(hDC, 0, size.cy * i, textBuffer[i], letterCnt);
        }
    }

    GetTextExtentPoint32W(hDC, textBuffer[pos.y], pos.x + 1, &size);
    SetCaretPos(size.cx - 8, size.cy * pos.y);

    EndPaint(hWnd, &ps);
}

void Message::OnDestroy(HWND hWnd)
{
    HideCaret(hWnd);
    DestroyCaret();
    PostQuitMessage(0);
}
