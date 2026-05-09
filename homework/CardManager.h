#pragma once

#pragma once

#include "Card.h"

class CardManager
{
private:
    std::vector<Card*> allCards;

    std::vector<Card*> drawPile;    // 덱
    std::vector<Card*> hand;        // 손패
    std::vector<Card*> discardPile; // 버린카드더미
    std::vector<Card*> exhausted;   // 소멸

public:
    int getDeckCount() { return drawPile.size(); }
    int getHandCount() { return hand.size(); }
    int getDiscardCount() { return discardPile.size(); }

    // 카드 추가
    void add(NameEnum name);

    // 선택한 카드 이동용
    void move(POINT p);

    // 덱 섞기
    void shuffleDeck();
    
    // 카드 선택
    void selectCard(POINT mousePos);
    void selectCard(int idx);
    
    // 카드 사용
    void useCard(POINT mousePos);

    // 카드 뽑기
    void drawCards(int count); 

    // 카드 버리기
    void discardCard();

    // 카드 소멸
    void exhaustCard();

    // 턴 종료할 때 불러야 하는 함수
    void endTurn();            

    // 그리기
    void draw(HDC hDC, HDC mDC);
};
inline CardManager cardManager;