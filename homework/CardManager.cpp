#include "CardManager.h"
#include "global.h"
#include <ranges>

void CardManager::add(NameEnum name)
{
    Card* tmp = new Card;
    tmp->initialize(name);
    drawPile.push_back(tmp);
}

void CardManager::move(POINT p)
{
    if (handIdx < 0) return;

    hand[handIdx]->move(p);
}

void CardManager::shuffleDeck()
{
    std::shuffle(drawPile.begin(), drawPile.end(), gen);
}

void CardManager::selectCard(POINT mousePos)
{
    if (hand.empty())
    {
        handIdx = -1;
        return;
    }

    for (size_t i{ hand.size() - 1 }; i >= 0; --i)
    {
        if (hand[i]->checkClick(mousePos))
        {
            handIdx = i;
            return;
        }
    }

    handIdx = -1;
    return;
}

void CardManager::useCard(POINT mousePos)
{
    if (handIdx < 0) return;

    hand[handIdx]->play();

    if (hand[handIdx]->getExhaust())
    {
        exhaustCard();
    }
    else
    {
        discardCard();
    }
    
    handIdx = -1;
}

void CardManager::drawCards(int count)
{
    for (int i = 0; i < count; ++i)
    {
        if (drawPile.empty())
        {
            if (discardPile.empty()) break;

            drawPile = discardPile;
            discardPile.clear();
            shuffleDeck();
        }

        hand.push_back(drawPile.back());
        drawPile.pop_back();
    }
}

void CardManager::discardCard()
{
    if (handIdx < 0 || handIdx >= hand.size())
    {
        MessageBox(ws.hWnd, L"카드 버리기 오류", L"오류", MB_OK);
        return;
    }

    discardPile.push_back(hand[handIdx]);
    hand.erase(hand.begin() + handIdx);
}

void CardManager::exhaustCard()
{
    if (handIdx < 0 || handIdx >= hand.size())
    {
        MessageBox(ws.hWnd, L"카드 버리기 오류", L"오류", MB_OK);
        return;
    }

    exhausted.push_back(hand[handIdx]);
    hand.erase(hand.begin() + handIdx);
}

void CardManager::endTurn()
{
    discardPile.insert(discardPile.end(),
        std::make_move_iterator(hand.begin()),
        std::make_move_iterator(hand.end()));
    hand.clear();
}

void CardManager::draw(HDC hDC, HDC mDC)
{
    if (hand.empty()) return;

    POINT startPos{ ws.width / 2, ws.height * 9 / 10 };
    int pos_xDiff = ws.width / 10;

    startPos.x -= (hand.size() - 1) * pos_xDiff/2;

    for (int i{}; i < hand.size(); ++i, startPos.x += pos_xDiff)
    {
        // 마우스로 선택한 카드는 따로 그릴 예정
        if (i == handIdx)
        {
            hand[i]->draw(hDC, mDC);
        }
        else
        {
            hand[i]->draw(hDC, mDC, startPos);
        }
    }
}
