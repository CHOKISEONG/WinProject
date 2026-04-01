#include "global.h"

RECT rect1, rect2;
LPRECT rect3;
POINT point;
unsigned int rect1Color, rect2Color;
Color triColor, rectColor, circleColor;

std::random_device rd;
unsigned __int64 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_int_distribution<int> uid(0, 9999);
std::uniform_int_distribution<int> uidColor(0, 255);

void createRect()
{
    rect1.left = 0;
    rect1.top = 0;
    rect1.right = uid(gen) % WIDTH;
    rect1.bottom = uid(gen) % HEIGHT;

    rect2.left = uid(gen) % WIDTH;
    rect2.top = uid(gen) % HEIGHT;
    rect2.right = WIDTH;
    rect2.bottom = HEIGHT;
}

void drawTriangle(HDC hDC)
{
    POINT tmp[3]{};
    for (int i{}; i < 5; ++i)
    {
        while (true)
        {
            point.x = uid(gen) % (rect1.right - rect1.left) + rect1.left;
            point.y = uid(gen) % (rect1.bottom - rect1.top) + rect1.top;

            if (!PtInRect(&rect2, point)) break;
        }

        tmp[0].x = point.x;
        tmp[0].y = point.y - LENGTH;

        tmp[1].x = point.x - LENGTH;
        tmp[1].y = point.y + LENGTH;

        tmp[2].x = point.x + LENGTH;
        tmp[2].y = point.y + LENGTH;

        Polygon(hDC, tmp, 3);
    }
}

void drawRectangle(HDC hDC, HBRUSH& brush)
{
    RECT tmp;
    for (int i{}; i < 5; ++i)
    {
        while (true)
        {
            point.x = uid(gen) % (rect2.right - rect2.left) + rect2.left;
            point.y = uid(gen) % (rect2.bottom - rect2.top) + rect2.top;

            if (!PtInRect(&rect1, point)) break;
        }
        tmp.left = point.x - LENGTH;
        tmp.top = point.y - LENGTH;
        tmp.right = point.x + LENGTH;
        tmp.bottom = point.y + LENGTH;
        FillRect(hDC, &tmp, brush);
    }
}

void drawCircle(HDC hDC)
{
}
