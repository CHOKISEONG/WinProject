#pragma once

#include "Image.h"
#include <vector>
#include <deque>

class Pacman : public Image
{
public:
	POINT dir;
	float speed = 1.0f;

	float animT{};

	bool otherAnim = false;

	void initialize();

	void move();

	void animation();

	void setDir(POINT _dir) { dir = _dir; }

	RECT getRect() const
	{
		int r = rad - 3;
		return RECT{ pos.x - r, pos.y - r, pos.x + r, pos.y + r };
	}

	void setBPos(POINT _bPos) { bPos = _bPos; }

	void makeChild();
};

inline Pacman player;

// player를 따라다니는 자식 팩맨(최대 3) + 이동 트레일
inline std::vector<Pacman> pacmanChildren;
inline std::deque<POINT> pacmanTrail;

void OtherAnimTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);
void JumpTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime);