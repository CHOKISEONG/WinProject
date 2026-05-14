#pragma once

#include "Image.h"

class Food : public Image
{
public:
	Food(POINT p);
};
inline std::vector<Food> foods;