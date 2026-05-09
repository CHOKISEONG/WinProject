#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();

	void tick() override;

	void defense(int num) { block += num; }
	void applyEnemyPattern(StatePattern pattern);

	// 나중에 게임매니저로 옮겨야 될 함수들
	int getMp() const { return mp; }
	void showMp(HDC hDC);
	void applyCardMp(int cardMp) { mp -= cardMp;  }
	void startTurn();
	void endTurn();
	bool isEnemyTurn = false;

private:
	int orgMp{ 3 };
	int mp{ 3 };
	
};
inline Player* ironclad;

void NextTurnTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);