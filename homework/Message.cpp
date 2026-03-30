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
        int letterCnt = getLetterLength(i, textBuffer[i]);
        TCHAR buff[99];
        if (letterCnt != 0)
        {
            if (printType.addTapToNum || printType.changeToC || printType.deleteSpace || printType.putInParentheses)
            {
                int idx{};
                if (printType.addTapToNum)
                {
                    for (int j{}; j < MAX_LETTER; ++j)
                    {
                        if (textBuffer[i][j] >= '0' && textBuffer[i][j] <= '9')
                        {
                            buff[idx++] = '*';
                            buff[idx++] = '*';
                            buff[idx++] = '*';
                            buff[idx++] = '*';
                        }
                        buff[idx++] = textBuffer[i][j];
                    }
                }
                if (printType.changeToC)
                {
                    std::map<TCHAR, int> myMap;
                    for (int i{}; i < idx; ++i)
                    {
                        ++myMap[buff[i]];
                    }
                    TCHAR maxChar;
                    int maxNum{ -1 };
                    for (const auto& m : myMap)
                    {
                        if (m.second > maxNum)
                        {
                            maxChar = m.first;
                            maxNum = m.second;
                        }
                    }

                    for (int i{}; i < idx; ++i)
                    {
                        if (buff[i] == maxChar)
                        {
                            buff[i] = '@';
                        }
                    }
                }
                if (printType.putInParentheses)
                {

                }
                if (printType.deleteSpace)
                {

                }
                
                // 뒤에 불필요한 문자도 보이는 문제 발생
                idx = getLetterLength(0, buff, 99);
                GetTextExtentPoint32W(hDC, buff, idx, &size);
                TextOutW(hDC, 0, size.cy * i, buff, idx);
            }
            else
            {
                GetTextExtentPoint32W(hDC, textBuffer[i], letterCnt, &size);
                TextOutW(hDC, 0, size.cy * i, textBuffer[i], letterCnt);
            }
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
