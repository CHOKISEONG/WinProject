#include "Pacman.h"
#include "Board.h"

namespace
{
	constexpr int kMaxChildren = 3;
	constexpr int kChildRad = 16;              // 작은 팩맨 크기
	constexpr int kTrailSpacingFrames = 18;    // 자식 1마리당 뒤처지는 프레임 수
	constexpr int kTrailExtra = 30;            // 여유분
}

void Pacman::initialize()
{
	load(10);
	pos = { 100,100 };
	bWidth = bHeight = 32;
	rad = 32;
	tintColor = targetColor = RGB(255, 255, 0);

	// 새 게임/리셋 시 자식/트레일 초기화
	pacmanChildren.clear();
	pacmanTrail.clear();
}

void Pacman::move()
{
	pos.x += dir.x * speed;
	pos.y += dir.y * speed;

	if (pos.x < 0 || pos.x > ws.width || pos.y < 0 || pos.y > ws.height)
	{
		pos.x -= dir.x * speed;
		pos.y -= dir.y * speed;
	}
	else
	{
		for (int i{}; i < (int)board.collideRect.size(); ++i)
		{
			if (PtInRect(&board.collideRect[i], pos))
			{
				pos.x -= dir.x * speed;
				pos.y -= dir.y * speed;
				break;
			}
		}
	}

	RECT rt = getRect();

	for (int i = static_cast<int>(board.itemPos.size()) - 1; i >= 0; --i)
	{
		auto& b = board.itemPos[i];

		if (PtInRect(&rt, b))
		{
			board.itemPos.erase(board.itemPos.begin() + i);
			tintColor = board.items[i].getColorBrush();
			board.items.erase(board.items.begin() + i);
			rad += 2;
		}
	}

	// ---- 여기부터: 자식 추종 로직 (player만 갱신하도록) ----
	if (this != &player) return;

	// 1) 트레일 기록
	pacmanTrail.push_back(pos);

	// 트레일 크기 관리(자식 수에 맞게)
	const size_t needTrail =
		(pacmanChildren.size() + 1) * (size_t)kTrailSpacingFrames + (size_t)kTrailExtra;

	while (pacmanTrail.size() > needTrail)
		pacmanTrail.pop_front();

	// 2) 자식 위치 갱신: "현재 위치에서 N프레임 이전"으로 이동
	for (size_t i = 0; i < pacmanChildren.size(); ++i)
	{
		const size_t delay = (i + 1) * (size_t)kTrailSpacingFrames;

		if (pacmanTrail.size() > delay)
		{
			const size_t idx = pacmanTrail.size() - 1 - delay;
			pacmanChildren[i].pos = pacmanTrail[idx];
		}
		else if (!pacmanTrail.empty())
		{
			pacmanChildren[i].pos = pacmanTrail.front();
		}
	}
}

void Pacman::animation()
{
	animT += 0.1f;
	if (animT > 2.0f)
	{
		animT = 0.0f;
	}

	if (dir.x == 0)
	{
		if (dir.y > 0)
		{
			bPos.y = bHeight * 3;
		}
		else if (dir.y < 0)
		{
			bPos.y = bHeight * 2;
		};

		bPos.x = (animT < 1.0f) ? 0 : bWidth;
	}
	else if (dir.y == 0)
	{
		if (dir.x > 0)
		{
			bPos.y = 0;
		}
		else if (dir.x < 0)
		{
			bPos.y = bHeight;
		};

		bPos.x = (animT < 1.0f) ? 0 : bWidth;
	}

	if (otherAnim)
	{
		bPos.y = bHeight * 4;
	}

	// 자식들은 플레이어 애니메이션 프레임/색상만 따라가게(간단 버전)
	if (this == &player)
	{
		for (auto& c : pacmanChildren)
		{
			c.bPos = bPos;
			c.tintColor = tintColor;
			c.targetColor = targetColor;
		}
	}
}

void Pacman::makeChild()
{
	if (pacmanChildren.size() >= (size_t)kMaxChildren)
		return;

	Pacman c;
	c.load(10);

	// sprite는 동일, 출력 크기(rad)만 줄여서 "작게" 보이게
	c.bWidth = 32;
	c.bHeight = 32;
	c.rad = kChildRad;

	c.pos = pos;
	c.dir = dir;

	// 색/투명색은 플레이어와 동일하게 맞춤
	c.targetColor = targetColor;
	c.tintColor = tintColor;

	// 생성 직후 튀지 않게 트레일을 현재 위치로 약간 채움
	const size_t need = (pacmanChildren.size() + 1) * (size_t)kTrailSpacingFrames + 1;
	while (pacmanTrail.size() < need)
		pacmanTrail.push_back(pos);

	pacmanChildren.push_back(c);
}

void OtherAnimTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	static float t = 0.0f;
	t += 0.01f;
	if (t < 1.0f)
	{
		player.otherAnim = true;
	}
	else
	{
		player.otherAnim = false;
		t = 0.0f;
		KillTimer(hWnd, 1);
	}
}

void JumpTimer(HWND hWnd, UINT iMsg, UINT idEvent, DWORD dwTime)
{
	static float jumpT = 0.0f;
	jumpT += 0.4f;

	if (jumpT < 15.0f)
	{
		if (player.dir.y == 0)
		{
			player.pos.y -= 1;
		}
		else
			player.pos.x -= 1;
	}
	else if (jumpT < 30.0f)
	{
		if (player.dir.y == 0)
		{
			player.pos.y += 1;
		}
		else
			player.pos.x += 1;
	}
	else
	{
		jumpT = 0.0f;
		KillTimer(hWnd, 3);
	}
}
