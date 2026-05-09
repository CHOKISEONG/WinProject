#include "Character.h"

void Character::tick()
{
}

void Character::damaged(int num)
{
	if (block > 0)
	{
		block -= num;
		if (block < 0)
		{
			hp += block;
			block = 0;
		}
	}
	else
	{
		hp -= num;
	}

	if (hp <= 0)
	{
		hp = 0;
		animTypes.push(AnimType::Death);
	}
}

void Character::drawWithState(HDC hDC, HDC mDC)
{
	POINT statePos{ pos.x + dPos.x, pos.y + dPos.y - drawHeight * 2 / 3 };

	// hp 출력
	std::wstring str = L"HP:" + std::to_wstring(hp);
	TextOut(hDC, statePos.x, statePos.y, str.c_str(), str.size());

	// 방어도 출력
	if (block > 0)
	{
		statePos.y -= 20;
		str = L"방어도:" + std::to_wstring(block);
		TextOut(hDC, statePos.x, statePos.y, str.c_str(), str.size());
	}

	draw(hDC, mDC);
}
