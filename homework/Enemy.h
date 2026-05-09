#pragma once

#include "Enum.h"
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();

	void tick() override;

	void attack();

	void showCurrentPattern(HDC hDC);

private:
	std::vector<StatePattern> pattern;
};
inline std::vector<Enemy*> enemies;