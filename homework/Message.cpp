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

        TCHAR buff[256]{};

        if (letterCnt != 0)
        {
            if (printType.addTapToNum || printType.changeToC || printType.deleteSpace || printType.putInParentheses)
            {
                int idx{};
                for (int j{}; j < MAX_LETTER && textBuffer[i][j] != NULL && idx < 98; ++j)
                {
                    buff[idx++] = textBuffer[i][j];
                }
                buff[idx] = NULL;

                if (printType.addTapToNum)
                {
                    int out{};
                    for (int j{}; j < MAX_LETTER; ++j)
                    {
                        if (textBuffer[i][j] >= '0' && textBuffer[i][j] <= '9')
                        {
                            buff[out++] = '*';
                            buff[out++] = '*';
                            buff[out++] = '*';
                            buff[out++] = '*';
                        }
                        buff[out++] = textBuffer[i][j];
                    }
                }
                idx = getLetterLength(0, buff, 256);
                if (printType.changeToC)
                {
                    std::map<TCHAR, int> myMap;
                    for (int i{}; i < idx; ++i)
                    {
                        ++myMap[buff[i]];
                    }

                    auto it = std::max_element(myMap.begin(), myMap.end(),
                        [](const auto& a, const auto& b) {
                            return a.second < b.second;
                        });

                    for (int k{}; k < idx; ++k)
                    {
                        if (buff[k] == it->first)
                        {
                            buff[k] = L'@';
                        }
                    }
                }
                idx = getLetterLength(0, buff, 256);
                if (printType.putInParentheses)
                {
                    int out{};
                    bool bracketOn{ false };

                    for (int i{}; i < idx; ++i, ++out)
                    {
                        if (buff[out] != ' ')
                        {
                            if (!bracketOn)
                            {
                                bracketOn = true;
                                for (int j{ 255 }; j > out; --j)
                                {
                                    buff[j] = buff[j - 1];
                                }
                                buff[out++] = '(';
                            }

                            buff[out] = toupper(buff[out]);
                        }
                        else if (buff[out] == ' ')
                        {
                            if (bracketOn)
                            {
                                bracketOn = false;
                                for (int j{ 255 }; j > out; --j)
                                {
                                    buff[j] = buff[j - 1];
                                }
                                buff[out++] = ')';
                            }
                        }
                    }

                    idx = getLetterLength(0, buff, 256);
                    if (bracketOn)
                        buff[idx] = ')';
                }

                idx = getLetterLength(0, buff, 256);
                if (printType.deleteSpace)
                {
                    for (int i{}; i < idx; ++i)
                    {
                        if (buff[i] == ' ')
                        {
                            for (int j{ i }; j < 255; ++j)
                            {
                                buff[j] = buff[j + 1];
                            }
                            --i;
                        }
                        else
                        {
                            buff[i] = tolower(buff[i]);
                        }
                    }
                }

                idx = getLetterLength(0, buff, 256);
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

    GetTextExtentPoint32W(hDC, textBuffer[pos.y], pos.x, &size);
    int x{ size.cx };
    // if (x < 0) x = 0;
    SetCaretPos(x, 16 * pos.y);

    EndPaint(hWnd, &ps);
}

void Message::OnDestroy(HWND hWnd)
{
    HideCaret(hWnd);
    DestroyCaret();
    PostQuitMessage(0);
}
