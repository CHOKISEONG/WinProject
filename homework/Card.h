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

    void initialize(NameEnum name);
    void draw(HDC hDC, HDC mDC);
    void draw(HDC hDC, HDC mDC, POINT pos);
    void draw(HDC hDC, HDC mDC, int handCount, int handIdx);

    bool checkClick(POINT p);

    void move(POINT p);

    void play();

    bool getExhaust() const { return isExhaust; }
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