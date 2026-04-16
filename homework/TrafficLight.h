#pragma once

#include <vector>
#include <memory>
#include "Observer.h"
#include "Shape.h"

class TrafficLight
{
private:
	std::vector<Shape> trafficLight;
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
	}
};

inline TrafficLight trafficLight;
