#pragma once

#include "Image.h"

class Enemy : public Image
{
public:
	void move() { pos.x += 10; }
};
inline Enemy enemy;