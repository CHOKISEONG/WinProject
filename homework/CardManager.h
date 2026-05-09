#pragma once

#pragma once

#include "Card.h"

class CardManager
{
private:
    std::vector<Card*> allCards;

    std::vector<Card*> drawPile;    // 덱
    std::vector<Card*> hand;        // 손패
    std::vector<Card*> discardPile; // 묘지
    std::vector<Card*> exhausted;   // 소멸

public:
    void add(NameEnum name);
    void move(POINT p);

    void shuffleDeck();             // 덱 섞기
    void selectCard(POINT mousePos);
    void useCard(POINT mousePos);
    void drawCards(int count);      // 덱 -> 손패
    void discardCard();             // 손패 -> 묘지
    void exhaustCard();             // 손패 -> 소멸
    void endTurn();                 // 턴 종료

    void draw(HDC hDC, HDC mDC);
};
inline CardManager cardManager;