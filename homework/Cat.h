#pragma once

#include "Image.h"

class Cat : public Image
{
private:
	POINT dir{1,1};

	int bmpMaxWidth{};
	int bmpMaxHeight{};

	int spriteWidth = 32;
	int spriteHeight = 32;

	

public:
	float speed = 0.3f;

	void initialize();
	void moves();
	void move(int speedMult = 1, POINT p = {});
	void animate();

	void changeSpeed(float mult)
	{
		speed += mult;
	}
};

inline Cat cat;