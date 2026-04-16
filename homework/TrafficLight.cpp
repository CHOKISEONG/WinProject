#include "TrafficLight.h"

void TrafficLight::initialize()
{
	trafficLight.clear();
	pos.clear();

	int cellLen = (ws.WIDTH > ws.HEIGHT) ? ws.HEIGHT / 60 : ws.WIDTH / 60;

	int cellH = (int)(ws.HEIGHT * 0.16666f);
	int cellW = (int)(ws.WIDTH * 0.16666f);
	POINT dPos = POINT{ cellW / 12, cellH / 2 };
	POINT light1{ cellW * 2 + dPos.x, cellH * 2 + dPos.y };
	POINT light2{ cellW * 4 - dPos.y, cellH * 4 - dPos.x };

	trafficLight.resize(6);

	for (int i{}; i < 4; i += 3)
	{
		trafficLight[i].setShape(Type::CIRCLE, cellLen);
		trafficLight[i].setColorBrush(RGB(204, 0, 0));

		trafficLight[i + 1].setShape(Type::CIRCLE, cellLen);
		trafficLight[i + 1].setColorBrush(RGB(255, 165, 0));

		trafficLight[i + 2].setShape(Type::CIRCLE, cellLen);
		trafficLight[i + 2].setColorBrush(RGB(0, 168, 120));
	}

	pos.push_back(POINT{ light1.x, light1.y - cellLen* 2 });
	pos.push_back(POINT{ light1.x, light1.y });
	pos.push_back(POINT{ light1.x, light1.y + cellLen * 2 });

	pos.push_back(POINT{ light2.x - cellLen * 2, light2.y});
	pos.push_back(POINT{ light2.x, light2.y});
	pos.push_back(POINT{ light2.x + cellLen * 2, light2.y});
}

void TrafficLight::draw(HDC hDC)
{
	for (int i{}; i < 4; i += 3)
	{
		trafficLight[i].draw(hDC, pos[i]);
		trafficLight[i + 1].draw(hDC, pos[i + 1]);
		trafficLight[i + 2].draw(hDC, pos[i + 2]);
	}
}
