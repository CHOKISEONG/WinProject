#include "Player.h"
#include "CardManager.h"
#include "Enemy.h"

Player::Player()
{
	hp = 80;
	load(NameEnum::아이언클래드);
}

void Player::tick()
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

	case AnimType::Damaged:
	{
		float pingPong = sin(t * 4 * PI);
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
	default:
		break;
	}
}

void Player::applyEnemyPattern(StatePattern pattern)
{
	if (pattern.damage > 0)
	{
		damaged(pattern.damage);
		play(AnimType::Damaged);
	}
}

void Player::showMp(HDC hDC)
{
	std::wstring str = L"마나:" + std::to_wstring(mp);
	TextOut(hDC, 0, ws.height / 2, str.c_str(), str.size());
}

void Player::startTurn()
{
	cardManager.drawCards(5);
	block = 0;
	mp = orgMp;
}

void Player::endTurn()
{
	cardManager.endTurn();

	// 임시로 턴 종료하면 잠시 뒤에 다시 startTurn 부르게 함
	SetTimer(ws.hWnd, 99, 1000, (TIMERPROC)NextTurnTimer);

	enemies[0]->setBlock(0);
	isEnemyTurn = true;
}

void NextTurnTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	ironclad->isEnemyTurn = false;
	enemies[0]->attack();
	ironclad->startTurn();
	KillTimer(ws.hWnd, idEvent);
}
