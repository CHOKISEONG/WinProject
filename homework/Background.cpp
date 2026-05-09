#include "Background.h"

void Background::initBG()
{
	images.push_back(new Image());
	images.back()->load(NameEnum::배경);
}
