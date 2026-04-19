#pragma once

#include "Shape.h"
#include "Observer.h"

class Car : public Observer
{
private:
	Shape body;
	RECT collider;

	POINT pos;
	std::vector<POINT> dPos; // 이동할 방향의 차 앞쪽 위치
	Direction dir; // 이동 방향

	float speed = 1.0f;			// 현재 속도
	float dSpeed = 1.0f;		// 전진 속도
	float reverseSpeed = -4.0f;	// 후진 속도
	int radius = 0.0f;

	bool isMoving = true;
	bool checkCrossing = false;
public:
	
	Direction getDir() const { return dir; }
	RECT getRect() const;
	void setDir(Direction d) { dir = d; }
	void setPos(POINT p);
	
	bool isInside(POINT p);
	bool isCollide(POINT p);
	void checkCollide();
	void checkSignal();

	void initialize(Direction d);
	void move();
	void setMoving(bool b) { isMoving = b; }

	void changeSpeed(float f) { if(dSpeed + f > 0.0f) dSpeed += f; }

	void draw(HDC hDC) const;

	virtual void OnNotify(TrafficSignal signal) override;
};

inline std::vector<std::shared_ptr<Car>> cars;