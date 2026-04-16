#pragma once

#include "global.h"

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify(TrafficSignal signal) = 0;
};