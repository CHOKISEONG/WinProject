#pragma once

#include <vector>
#include <memory>
#include "Observer.h"
#include "Shape.h"

class TrafficLight
{
private:
	// 0~2 : 좌우 신호등, 3~5 : 상하 신호등
	std::vector<Shape> trafficLight;
	TrafficSignal curSignal = TrafficSignal::YELLOW;
	int radius = 0;
	std::vector<POINT> pos;

	std::vector<std::weak_ptr<Observer>> observers;

public:
	void initialize();

	void draw(HDC hDC);

	void AddObserver(std::shared_ptr<Observer> observer)
	{
		observers.push_back(observer);
	}

	void Notify(TrafficSignal signal)
	{
		for (auto it{ observers.begin() }; it != observers.end();)
		{
			if (auto s_ptr = it->lock())
			{
				s_ptr->OnNotify(signal);
				++it;
			}
			else
			{
				it = observers.erase(it);
			}
		}

		OnNotify(signal);
	}

	void OnNotify(TrafficSignal signal);

	POINT getPos(int idx) const { return pos[idx]; }
	int getRad() const { return radius; }
	TrafficSignal getSignal() { return curSignal; }
	void setThickness(int a, int b);
};

inline TrafficLight trafficLight;

void LightTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);

void SwitchTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);