#pragma once

#include "Shape.h"
#include "Observer.h"

class NPC : public Observer
{
private:
	std::vector<Shape> body;
	POINT curPos;
	POINT targetPos;
	Direction dir;
	float progress = 0.0f;

	POINT point[4];

	int radius;

	bool canCross = false;

public:
	void move(std::map<Direction,bool>& m);

	void draw(HDC hDC) const;

	void initialize();

	virtual void OnNotify(TrafficSignal signal) override;
};

inline std::shared_ptr<NPC> npc;