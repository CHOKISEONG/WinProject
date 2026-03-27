#include "global.h"

TCHAR textBuffer[MAX_LINE][MAX_LETTER + 1]{};
Pos pos{};

std::random_device rd;
unsigned __int64 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_int_distribution<int> uid(2, 20);
std::uniform_int_distribution<int> uidPos(0, HEIGHT);
std::uniform_int_distribution<int> uidColor(0, 255);

int getLetterLength(int line)
{
    int letterCnt = MAX_LETTER;

    for (int j{ MAX_LETTER - 1 }; j >= 0; --j)
    {
        if (textBuffer[line][j] != NULL)
            break;
        --letterCnt;
    }

    return letterCnt;
}