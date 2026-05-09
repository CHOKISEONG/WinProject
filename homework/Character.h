#pragma once

#include "Image.h"

class Character : public Image
{
public:
	// 애니메이션 추가
	void play(AnimType type) { animTypes.push(type); isAnimating = true; }

	// 한 틱마다 애니메이션 효과
	virtual void tick();
	virtual ~Character() = default;

	bool getAlive() const { return isAlive; }
	void damaged(int num);
	void setBlock(int num) { block = num; }

	// 기본 이미지 그리기 + 현재 상태 출력(임시)
	void drawWithState(HDC hDC, HDC mDC);

protected:
	// 체력
	int hp{};

	// 가지고 있는 방어도
	int block{};

	// 살아있는지 체크용
	bool isAlive = true;

	// 가지고 있는 상태이상들
	std::vector<Effect> effects;

	/// <summary>
	/// 애니메이션 용 변수들.
	/// 큐에 들어온 순서대로 처리함
	/// </summary>
	std::queue<AnimType> animTypes;
	float t = 0.0f;
	float animSpeed = 15.0f;
	bool isAnimating = false;
};