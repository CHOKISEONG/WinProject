#pragma once

enum class NameEnum : int
{
	강타, 기사회생, 낙인, 난타, 녹아내리는주먹, 대화재, 돌갑옷,
	몸통박치기, 무감각, 무자비, 무적, 바리케이드, 박치기, 발화, 분노, 불타는조약, 사혈, 쇄도, 수비,
	싸움준비, 악랄함, 악마의눈, 연쇄, 이중타격, 전투최면, 전투의북소리, 정면돌파, 제물, 조약의끝,
	지옥불, 짓밟기, 타격, 파열, 포악함, 피의벽, 핏빛망토, 해체, 협박, 화염장벽, 흘려보내기
	, 아이언클래드, 배경
};

enum class CardLocation
{
	DECK,       // 덱
	HAND,       // 손패
	DISCARD,    // 묘지
	EXHAUSTED   // 소멸
};

enum class EffectEnum
{
	// 효과없음
	NONE,
	// 취약
	Vulnerable,
	// 약화
	Weak,
	// 힘
	Strength,
	// 판금
	Plating,
};
struct Effect
{
	// 효과
	EffectEnum effectData = EffectEnum::NONE;
	
	// 지속시간
	int duration{};
};

enum class AnimType
{
	Attack,
	Defense,
	Debuff,
	Buff
};