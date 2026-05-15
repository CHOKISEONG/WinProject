#pragma once

#include "Image.h"

class Cat : public Image
{
private:

	int bmpMaxWidth{};
	int bmpMaxHeight{};

	int spriteWidth = 32;
	int spriteHeight = 32;

public:
	int speed = 4;

	void initialize();
	void move(Direction d);
	void animate();

	void changeSpeed(float mult)
	{
		speed += mult;
	}
};

inline Cat cat;