#pragma once

#include "Image.h"
#include <map>

struct CardData {
	int cost;
	int damage;
	int defense;
	std::vector<Effect> effects;
    bool isExhaust = false;
};

class Card
{
public:
    // 카드DB 초기화
    static void initDatabase();

    // 초기화
    void initialize(NameEnum name);

    // 그리기
    void draw(HDC hDC, HDC mDC);
    void draw(HDC hDC, HDC mDC, POINT pos);

    // 인자로 받은 p가 나를 가리키는지
    bool checkClick(POINT p);

    // 이동
    void move(POINT p);
    void setPos(POINT p) { image.pos = p; }

    // 카드 사용
    void play();

    bool getExhaust() const { return isExhaust; }
    int getCost() const { return cost; }

private:
    static std::map<NameEnum, CardData> cardDB;

    // 개별 카드의 데이터
    Image image;
    int cost{};
    int damage{};
    int defense{};
    bool isExhaust{};
    std::vector<Effect> effect;
};