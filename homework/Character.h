#pragma once

#include "Image.h"

class Character : public Image
{
public:
	void play(AnimType type) { animTypes.push(type); isAnimating = true; }

	virtual void tick();

protected:
	int hp{};
	std::vector<Effect> effects;

	std::queue<AnimType> animTypes;
	float t = 0.0f;
	float animSpeed = 15.0f;
	bool isAnimating = false;
};