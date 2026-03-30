#include "global.h"

TCHAR textBuffer[MAX_LINE][MAX_LETTER + 1]{};
int curMaxLine{ 1 };
PrintType printType{};
bool isUpper = false;
Pos pos{};
LetterType type{ LetterType::OVERWRITE };

std::random_device rd;
unsigned __int64 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_int_distribution<int> uid(2, 20);
std::uniform_int_distribution<int> uidPos(0, HEIGHT);
std::uniform_int_distribution<int> uidColor(0, 255);

int getLetterLength(int line, TCHAR* textBuff, int num)
{
    int letterCnt = num;

    for (int j{ num - 1 }; j >= 0; --j)
    {
        if (textBuff[j] != NULL)
            break;
        --letterCnt;
    }

    return letterCnt;
}

int getMaxLine()
{
    for (int i{}; i < MAX_LINE; ++i)
    {
        if (getLetterLength(0, textBuffer[i], MAX_LETTER) == 0)
        {
            return i;
        }
    }

    return -1;
}

void addNumberToText(int addNum)
{
    TCHAR tmp;
    for (int i{}; i < MAX_LINE; ++i)
    {
        for (int j{}; j < MAX_LETTER; ++j)
        {
            tmp = textBuffer[i][j];
            if (tmp >= L'0' && tmp <= '9')
            {
                
                int num{ (_wtoi(&tmp) + addNum + 10) % 10};
                std::wstring ws = std::to_wstring(num);
                textBuffer[i][j] = *ws.c_str();
            }
        }
    }
}

void shiftLine()
{
    TCHAR start[MAX_LETTER + 1];
    memcpy(start, textBuffer[0], sizeof(TCHAR) * (MAX_LETTER + 1));
    for (int i{1}; i < MAX_LINE; ++i)
    {
        for (int j{}; j < MAX_LETTER; ++j)
        {
            textBuffer[i - 1][j] = textBuffer[i][j];
        }
    }
    memcpy(textBuffer[MAX_LINE - 1], start, sizeof(TCHAR) * (MAX_LETTER + 1));
}
