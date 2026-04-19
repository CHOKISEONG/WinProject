#include "Message.h"
#include "KeyHandler.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Car.h"
#include "NPC.h"
#include <string>

void Message::OnCreate(HWND hWnd)
{
	// event id를 관리해야할 필요가 느껴질 때 두번째 인자 수정하기
	SetTimer(hWnd, 0, TimerFuncFPS, (TIMERPROC)TimerFunc);

	int cellW = ws.WIDTH / 12;
	int cellH = ws.HEIGHT / 12;

	cars.clear();

	struct CarInfo { Direction dir; POINT pos; };
	CarInfo carInfos[8] = {
		{ Direction::LEFTDIR,  POINT{ cellW, cellH * 5 } },
		{ Direction::LEFTDIR,  POINT{ cellW * 10, cellH * 5 } },
		{ Direction::RIGHTDIR, POINT{ cellW, cellH * 7 } },
		{ Direction::RIGHTDIR, POINT{ cellW * 10, cellH * 7 } },
		{ Direction::UPDIR,    POINT{ cellW * 7, cellH } },
		{ Direction::UPDIR,    POINT{ cellW * 7, cellH * 10 } },
		{ Direction::DOWNDIR,  POINT{ cellW * 5, cellH } },
		{ Direction::DOWNDIR,  POINT{ cellW * 5, cellH * 10 } }
	};

	for (int i = 0; i < 8; ++i)
	{
		auto c = std::make_shared<Car>();
		c->initialize(carInfos[i].dir);
		c->setPos(carInfos[i].pos);
		
		cars.push_back(c);
		trafficLight.AddObserver(c);
	}
	
	trafficLight.initialize();

	road.initialize();

	npc = std::make_shared<NPC>();
	npc->initialize();
	trafficLight.AddObserver(npc);

	ws.hWnd = hWnd;
}

void Message::TimerFunc(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	for (auto& c : cars)
	{
		c->checkCollide();
		c->checkSignal();
		c->move();
	}

	npc->move(road.checkCross());

	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);

	SetROP2(hDC, currentROP2);

	road.draw(hDC);

	for (const auto& c : cars)
		c->draw(hDC);

	trafficLight.draw(hDC);

	npc->draw(hDC);

	EndPaint(hWnd, &ps);
}

void Message::LMouseClick()
{
	for (int i{}; i < 6; ++i)
	{
		if (trafficLight.getRad() > getDistance(trafficLight.getPos(i), ws.mousePos))
		{
			if (i == 0 || i == 5)
			{
				trafficLight.Notify(TrafficSignal::RED);
				return;
			}
			else if (i == 1 || i == 4)
			{
				trafficLight.Notify(TrafficSignal::YELLOW);
				return;
			}
			else
			{
				trafficLight.Notify(TrafficSignal::GREEN);
				return;
			}
		}
	}

	trafficLight.Notify(TrafficSignal::RED_ALL);
}

void Message::RMouseClick()
{
	SetTimer(ws.hWnd, 999, 100, (TIMERPROC)WaitTimer);
}

void Message::LMouseDBClick()
{
}

void Message::RMouseDBClick()
{
}

void Message::OnKeyDown(HWND hWnd, WPARAM wParam)
{
	switch (wParam)
	{
	case VK_UP:case VK_DOWN:case VK_LEFT:case VK_RIGHT:
	case VK_ESCAPE:case VK_BACK:case VK_RETURN:case VK_TAB:
	case VK_HOME:case VK_END:case VK_INSERT:
	case VK_DELETE:case VK_PRIOR:case VK_NEXT:
	case VK_F1:case VK_F2:case VK_F3:case VK_F4:
	case VK_F5:case VK_F6:case VK_F7:case VK_F8:
	case VK_OEM_PLUS: case VK_OEM_MINUS:
		KeyHandler::KeyDown(hWnd, wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		return;
	default:
		KeyHandler::Default(hWnd, wParam);
		break;
	}

	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnKeyUp(HWND hWnd, WPARAM wParam)
{
	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnChar(HWND hWnd, WPARAM wParam)
{
	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::OnSize(HWND hWnd, int width, int height)
{
	ws.WIDTH = width;
	ws.HEIGHT = height;

	road.initialize();
	trafficLight.initialize();

	InvalidateRect(hWnd, NULL, TRUE);
}

void Message::MouseMove(int mouse_x, int mouse_y)
{
	ws.mousePos.x = mouse_x;
	ws.mousePos.y = mouse_y;
}

void Message::OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}
