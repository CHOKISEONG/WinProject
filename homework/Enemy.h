#pragma once

#include "Character.h"

class Enemy : public Character
{
public:
	virtual void tick() override;
};
inline Enemy enemy;