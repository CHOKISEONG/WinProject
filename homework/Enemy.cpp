#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
	NameEnum start = NameEnum::스컬킹;
	NameEnum end = NameEnum::스폰지밥;
	std::uniform_int_distribution<int> nameUid(
		static_cast<int>(start),
		static_cast<int>(end)
	);
	NameEnum selectedEnemy = static_cast<NameEnum>(nameUid(gen));
	load(selectedEnemy);

	switch (selectedEnemy)
	{
	case NameEnum::스컬킹:
		hp = 20;
		break;
	case NameEnum::스폰지밥:
		hp = 30;
		block = 10;
		break;
	default:
		break;
	}

	// 일단 랜덤으로 공격값,수비값 넣음
	for (int i{}; i < 5; ++i)
	{
		pattern.push_back(StatePattern{ uid(gen) % 10, uid(gen) % 10 });
	}

	setSize(POINT{ 100,200 });
}

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
		if (animTypes.front() == AnimType::Death)
		{
			isAlive = false;
		}

		t = 0.0f;
		dPos.x = 0;
		dPos.y = 0;
		animTypes.pop();
		return;
	}

	switch (animTypes.front())
	{
	case AnimType::Attack:
	{
		float pingPong = 1.0f - fabsf(2.0f * t - 1.0f);
		int maxValue = -100;
		int currentVal = static_cast<int>(maxValue * pingPong);
		dPos.x = currentVal * 2;
	}
	break;

	case AnimType::Damaged:
	{
		float pingPong = sin(t * 4 * PI);
		int maxValue = 50;
		int currentVal = static_cast<int>(maxValue * pingPong);
		dPos.x = currentVal;
	}
	break;

	case AnimType::Defense:
	{
		float pingPong = 1.0f - fabsf(2.0f * t - 1.0f);
		int maxValue = 50;
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
	case AnimType::Death:
		dPos.y = t * ws.height / 2;
		break;
	default:
		break;
	}
}

void Enemy::attack()
{
	play(AnimType::Attack);
	ironclad->applyEnemyPattern(pattern[0]);
	block += pattern[0].deffense;
	std::rotate(pattern.begin(), pattern.begin() + 1, pattern.end());
}

void Enemy::showCurrentPattern(HDC hDC)
{
	std::wstring str = L"다음에 하는 행동";
	TextOut(hDC, pos.x, 10, str.c_str(), str.size());
	str = L"공격:" + std::to_wstring(pattern[0].damage);
	TextOut(hDC, pos.x, 30, str.c_str(), str.size());
	str = L"방어:" + std::to_wstring(pattern[0].deffense);
	TextOut(hDC, pos.x, 50, str.c_str(), str.size());
}
