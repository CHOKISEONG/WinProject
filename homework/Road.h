#pragma once

#include "global.h"
#include "Shape.h"

class Road
{
private:
	Shape bkGround;
	std::vector<Shape> lines;
	std::vector<Shape> crossing;

public:
	void draw(HDC hDC)
	{
		bkGround.draw(hDC);

		for (const auto& c : crossing)
		{
			c.draw(hDC);
		}

		for (const auto& l : lines)
		{
			l.draw(hDC);
		}
	}

	void Initialize()
	{
		bkGround.clearAll();
		bkGround.setColorBrush(RGB(0,0,0));
		bkGround.setColorPen(RGB(0, 0, 0));
		bkGround.setType(Type::RECTANGLE);
		bkGround.addPoint(POINT{ 0,0 });
		bkGround.addPoint(POINT{ ws.WIDTH,0 });
		bkGround.addPoint(POINT{ ws.WIDTH,ws.HEIGHT });
		bkGround.addPoint(POINT{ 0,ws.HEIGHT });

		lines.clear();
		crossing.clear();

		int cellH = (int)(ws.HEIGHT * 0.16666f);
		int cellW = (int)(ws.WIDTH * 0.16666f);

		for (int i{}; i < 12; ++i)
		{
			lines.push_back(Shape(Type::LINE));
			lines[i].setColorPen(RGB(255, 255, 255));
		}
			

		// 가로 도로
		int idx{};
		int w[4]{ 0, cellW * 2, cellW * 4, ws.WIDTH };
		for (int i{}; i < 4; i += 2)
		{
			lines[idx].addPoint(POINT{ w[i], cellH * 2});
			lines[idx].addPoint(POINT{ w[i+1], cellH * 2 });
			lines[idx].setThickness(3);

			lines[idx + 1].addPoint(POINT{  w[i], cellH * 3 });
			lines[idx + 1].addPoint(POINT{  w[i+1], cellH * 3 });
			lines[idx + 1].setPenStyle(PS_DASHDOT);

			lines[idx + 2].addPoint(POINT{ w[i], cellH * 4 });
			lines[idx + 2].addPoint(POINT{ w[i+1], cellH * 4 });
			lines[idx + 2].setThickness(3);

			idx += 3;
		}

		// 세로 도로
		int h[4]{ 0, cellH * 2, cellH * 4, ws.HEIGHT };
		for (int i{}; i < 4; i += 2)
		{
			lines[idx].addPoint(POINT{ cellW * 2, h[i]});
			lines[idx].addPoint(POINT{ cellW * 2 , h[i + 1]});
			lines[idx].setThickness(3);

			lines[idx + 1].addPoint(POINT{ cellW * 3, h[i]});
			lines[idx + 1].addPoint(POINT{ cellW * 3, h[i + 1]});
			lines[idx + 1].setPenStyle(PS_DASHDOT);

			lines[idx + 2].addPoint(POINT{ cellW * 4, h[i] });
			lines[idx + 2].addPoint(POINT{ cellW * 4, h[i + 1] });
			lines[idx + 2].setThickness(3);

			idx += 3;
		}

		for (int i{}; i < 80; ++i)
		{
			crossing.push_back(Shape(Type::LINE));
		}
		for (int i{}; i < 80; ++i)
		{
			crossing[i].setColorPen(RGB(255, 255, 255));
			crossing[i].setColorBrush(RGB(255, 255, 255));
			crossing[i].setThickness(4);
		}
		
		
		for (int i{}; i < 20; ++i)
		{
			int cellLen = cellH / 10 * i;

			crossing[i].addPoint(POINT{ cellW, h[1] + cellLen});
			crossing[i].addPoint(POINT{ cellW * 2, h[1] + cellLen });
			crossing[40 + i].addPoint(POINT{ cellW * 4, h[1] + cellLen });
			crossing[40 + i].addPoint(POINT{ cellW * 5, h[1] + cellLen });
		}
		for (int i{20}; i < 40; ++i)
		{
			int cellLen = cellW / 10 * (i - 20);

			crossing[i].addPoint(POINT{ w[1] + cellLen, cellH});
			crossing[i].addPoint(POINT{ w[1] + cellLen, cellH * 2 });

			crossing[40 + i].addPoint(POINT{ w[1] + cellLen, cellH * 4 });
			crossing[40 + i].addPoint(POINT{ w[1] + cellLen, cellH * 5 });
		}
	}
};

inline Road road;