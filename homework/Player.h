#pragma once

#include "Image.h"

class Player : public Image
{
public:
	void play(AnimType type) { animTypes.push(type); isAnimating = true; }

	void tick();
private:
	int hp{ 80 };
	std::vector<Effect> effects;

	std::queue<AnimType> animTypes;
	float t = 0.0f;
	bool isAnimating = false;
};
inline Player ironclad;