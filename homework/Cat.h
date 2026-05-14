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
	void initialize();
	void move(int speedMult = 1);
	void animate();
};

inline Cat cat;