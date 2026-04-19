#include "TrafficLight.h"
#include "NPC.h"

void TrafficLight::OnNotify(TrafficSignal signal)
{
	KillTimer(ws.hWnd, 3);
	KillTimer(ws.hWnd, 4);

	if (signal == TrafficSignal::RED)
	{
		curSignal = TrafficSignal::RED;

		setThickness(0, 5);
	}
	else if (signal == TrafficSignal::YELLOW)
	{
		if (curSignal == TrafficSignal::RED)
		{
			SetTimer(ws.hWnd, 3, 1000, (TIMERPROC)LightTimer);
		}
		else
		{
			SetTimer(ws.hWnd, 4, 1000, (TIMERPROC)LightTimer);
		}

		setThickness(1, 4);
	}
	else if (signal == TrafficSignal::GREEN)
	{
		curSignal = TrafficSignal::GREEN;

		setThickness(2, 3);
	}
	else if (signal == TrafficSignal::RED_ALL)
	{
		curSignal = TrafficSignal::RED_ALL;
		setThickness(0, 3);
	}
}

void TrafficLight::setThickness(int a, int b)
{
	for (int i{}; i < 6; ++i)
	{
		if (i == a || i == b)
			trafficLight[i].setThickness(4);
		else
			trafficLight[i].setThickness(1);
	}
}

void TrafficLight::initialize()
{
	trafficLight.clear();
	pos.clear();

	radius = (ws.WIDTH > ws.HEIGHT) ? ws.HEIGHT / 60 : ws.WIDTH / 60;

	int cellH = (int)(ws.HEIGHT * 0.16666f);
	int cellW = (int)(ws.WIDTH * 0.16666f);
	POINT dPos = POINT{ cellW / 12, cellH / 2 };
	POINT light1{ cellW * 2 + dPos.x, cellH * 2 + dPos.y };
	POINT light2{ cellW * 4 - dPos.y, cellH * 4 - dPos.x };

	trafficLight.resize(6);

	for (int i{}; i < 4; i += 3)
	{
		trafficLight[i].setShape(Type::CIRCLE, radius);
		trafficLight[i].setColorBrush(RGB(204, 0, 0));
		trafficLight[i].setColorPen(RGB(255, 255, 255));

		trafficLight[i + 1].setShape(Type::CIRCLE, radius);
		trafficLight[i + 1].setColorBrush(RGB(255, 165, 0));
		trafficLight[i + 1].setColorPen(RGB(255, 255, 255));

		trafficLight[i + 2].setShape(Type::CIRCLE, radius);
		trafficLight[i + 2].setColorBrush(RGB(0, 168, 120));
		trafficLight[i + 2].setColorPen(RGB(255, 255, 255));
	}

	pos.push_back(POINT{ light1.x, light1.y - radius* 2 });
	pos.push_back(POINT{ light1.x, light1.y });
	pos.push_back(POINT{ light1.x, light1.y + radius * 2 });

	pos.push_back(POINT{ light2.x - radius * 2, light2.y});
	pos.push_back(POINT{ light2.x, light2.y});
	pos.push_back(POINT{ light2.x + radius * 2, light2.y});
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

void LightTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	if (idEvent == 3)
	{
		trafficLight.Notify(TrafficSignal::GREEN);
	}
	else if (idEvent == 4)
	{
		trafficLight.Notify(TrafficSignal::RED);
	}
}

void SwitchTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	trafficLight.Notify(TrafficSignal::YELLOW);
}

void WaitTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	if (npc->getDir() == Direction::STOP)
	{
		trafficLight.Notify(TrafficSignal::RED);
		KillTimer(hWnd, idEvent);
	}
}
