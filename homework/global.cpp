#include "global.h"

SZ ws;

RECT rect1, rect2;
LPRECT rect3;
POINT point;
unsigned int rect1Color, rect2Color;
Color triColor, rectColor, circleColor;
std::vector<POINT*> triangles, rects, circles;

std::random_device rd;
unsigned __int64 seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(static_cast<std::mt19937::result_type>(seed));
std::uniform_int_distribution<int> uid(0, 9999);
std::uniform_int_distribution<int> uidColor(0, 255);

void createRect()
{
    int width{}, height{};
    while (width < ws.WIDTH / 3 && height < ws.HEIGHT / 3)
    {
        width = uid(gen) % ws.WIDTH;
        height = uid(gen) % ws.HEIGHT;
    }

    rect1.left = (uid(gen) % ws.WIDTH) / 2;
    rect1.top = (uid(gen) % ws.HEIGHT) / 2;
    rect1.right = rect1.left + width;
    rect1.bottom = rect1.top + height;

    rect2.left = (uid(gen) % ws.WIDTH) / 2;
    rect2.top = (uid(gen) % ws.HEIGHT) / 2;
    rect2.right = rect2.left + width;
    rect2.bottom = rect2.top + height;

    rect1Color = uidColor(gen);
    rect2Color = uidColor(gen);
}

void makeTriangle()
{
    triColor.r = uidColor(gen);
    triColor.g = uidColor(gen);
    triColor.b = uidColor(gen);

    int triNum{ uid(gen) % 5 + 3 };

    triangles.clear();
    triangles.resize(triNum);

    for (int i{}; i < triNum; ++i)
    {
        while (true)
        {
            point.x = uid(gen) % (rect1.right - rect1.left) + rect1.left;
            point.y = uid(gen) % (rect1.bottom - rect1.top) + rect1.top;

            if (!PtInRect(&rect2, point)) break;
        }

        triangles[i] = new POINT[3];

        triangles[i][0].x = point.x;
        triangles[i][0].y = point.y - LENGTH;

        triangles[i][1].x = point.x - LENGTH;
        triangles[i][1].y = point.y + LENGTH;

        triangles[i][2].x = point.x + LENGTH;
        triangles[i][2].y = point.y + LENGTH;
    }
}

void makeRectangle()
{
    rectColor.r = uidColor(gen);
    rectColor.g = uidColor(gen);
    rectColor.b = uidColor(gen);

    int rectNum{ uid(gen) % 5 + 3 };

    rects.clear();
    rects.resize(rectNum);

    for (int i{}; i < rectNum; ++i)
    {
        while (true)
        {
            point.x = uid(gen) % (rect2.right - rect2.left) + rect2.left;
            point.y = uid(gen) % (rect2.bottom - rect2.top) + rect2.top;
            
            if (!PtInRect(&rect1, point)) break;
        }

        rects[i] = new POINT[4];

        rects[i][0].x = point.x - LENGTH;
        rects[i][0].y = point.y - LENGTH;

        rects[i][1].x = point.x + LENGTH;
        rects[i][1].y = point.y - LENGTH;

        rects[i][2].x = point.x + LENGTH;
        rects[i][2].y = point.y + LENGTH;

        rects[i][3].x = point.x - LENGTH;
        rects[i][3].y = point.y + LENGTH;
    }
}

void makeCircle()
{
    circleColor.r = uidColor(gen);
    circleColor.g = uidColor(gen);
    circleColor.b = uidColor(gen);

    int circleNum{ uid(gen) % 5 + 3 };

    circles.clear();
    circles.resize(circleNum);

    for (int i{}; i < circleNum; ++i)
    {
        while (true)
        {
            point.x = uid(gen) % ws.WIDTH;
            point.y = uid(gen) % ws.HEIGHT;

            if (!PtInRect(&rect1, point) && !PtInRect(&rect2, point)) break;
        }

        circles[i] = new POINT{};
        circles[i]->x = point.x;
        circles[i]->y = point.y;
    }
}

void drawTriangle(HDC hDC)
{
    HBRUSH hBrush, oldBrush;

    hBrush = CreateSolidBrush(RGB(triColor.r, triColor.g, triColor.b));
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    for (int i{}; i< triangles.size(); ++i)
            Polygon(hDC, triangles[i], 3);

    SelectObject(hDC, oldBrush);
    DeleteObject(hBrush);
}

void drawRectangle(HDC hDC, HBRUSH& brush)
{
    HBRUSH hBrush, oldBrush;

    hBrush = CreateSolidBrush(RGB(rectColor.r, rectColor.g, rectColor.b));
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    for (int i{}; i < rects.size(); ++i)
        Polygon(hDC, rects[i], 4);

    SelectObject(hDC, oldBrush);
    DeleteObject(hBrush);   
}

void drawCircle(HDC hDC)
{
    HBRUSH hBrush, oldBrush;

    hBrush = CreateSolidBrush(RGB(circleColor.r, circleColor.g, circleColor.b));
    oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

    for (int i{}; i < circles.size(); ++i)
        Ellipse(hDC, circles[i]->x - LENGTH, circles[i]->y - LENGTH, circles[i]->x + LENGTH, circles[i]->y + LENGTH);

    SelectObject(hDC, oldBrush);
    DeleteObject(hBrush);
}
