#include "MyString.h"

#include <cmath>
#include <algorithm>

#include <string>
#include <windows.h>

void printStr(HDC hDC, POINT start, POINT end, std::string& _str)
{
    std::shuffle(_str.begin(), _str.end(), gen);

    int n = static_cast<int>(_str.length());

    float xLen = static_cast<float>(end.x - start.x);
    float yLen = static_cast<float>(end.y - start.y);

    SetTextColor(hDC, RGB(uidColor(gen), uidColor(gen), uidColor(gen)));

    for (int i = 0; i < n; ++i)
    {
        float ratio = static_cast<float>(i) / (n - 1);

        float curX = start.x + xLen * ratio;
        float curY = start.y + yLen * ratio;

        TextOutA(hDC, curX, curY, &_str[i], 1);
    }
}
