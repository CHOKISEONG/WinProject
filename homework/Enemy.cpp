#include "Enemy.h"

void Enemy::tick()
{
	if (animTypes.empty())
	{
		t = 0.0f;
		isAnimating = false;
		dPos.x = 0;
		dPos.y = 0;
		return;
	}

	if (t < 1.0f)
	{
		t += animSpeed / TimerFuncFPS;
	}
	else
	{
		t = 0.0f;
		dPos.x = 0;
		dPos.y = 0;
		animTypes.pop();
		return;
	}

	//		  t: 0 -> 0.5 -> 1
	// pingpong: 0 -> 1 -  > 0
	float pingPong = 1.0f - fabsf(2.0f * t - 1.0f);

	switch (animTypes.front())
	{
	case AnimType::Attack:
	{
		int maxValue = -100;
		int currentVal = static_cast<int>(maxValue * pingPong);
		dPos.x = -currentVal * 2;
		dPos.y = currentVal;
	}
	break;
	case AnimType::Defense:
	{
		int maxValue = -50;
		int currentVal = static_cast<int>(maxValue * pingPong);
		dPos.x = currentVal;
	}
	break;
	case AnimType::Buff:
		// 개발 예정
		break;
	case AnimType::Debuff:
		// 개발 예정
		break;
	}
}