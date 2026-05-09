#pragma once

#include "Image.h"

struct Background
{
	void initBG();

	std::vector<Image*> images;
};
inline Background background;
