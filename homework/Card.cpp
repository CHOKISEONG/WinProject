#include "Card.h"
#include "Player.h"

std::map<NameEnum, CardData> Card::cardDB;

void Card::initDatabase()
{
    if (!cardDB.empty()) return;

    cardDB[NameEnum::강타] = CardData{ 2, 8, 0, {{EffectEnum::Vulnerable, 2}} };
    cardDB[NameEnum::수비] = CardData{ 1, 0, 5, {} };
    cardDB[NameEnum::타격] = CardData{ 1, 6, 0, {} };
}

void Card::initialize(NameEnum name)
{
    auto it = cardDB.find(name);
    if (it == cardDB.end()) {
        return;
    }

    const CardData& data = it->second;
    cost = data.cost;
    damage = data.damage;
    defense = data.defense;
    effect = data.effects;
    isExhaust = data.isExhaust;

    image.load(name);
}

void Card::draw(HDC hDC, HDC mDC)
{
    image.draw(hDC, mDC);
}

void Card::draw(HDC hDC, HDC mDC, POINT pos)
{
    image.pos = pos;
    image.draw(hDC, mDC);
}

void Card::draw(HDC hDC, HDC mDC, int handCount, int handIdx)
{
    // 개발 예정
    return;
}

bool Card::checkClick(POINT p)
{
    RECT rt{
        image.pos.x - image.drawWidth / 2,
        image.pos.y - image.drawHeight / 2,
        image.pos.x + image.drawWidth /2,
        image.pos.y + image.drawHeight / 2
    };

    if (PtInRect(&rt, p))
        return true;
    else
        return false;
}

void Card::move(POINT p)
{
    image.pos.x += p.x;
    image.pos.y += p.y;
}

void Card::play()
{
    // 지금은 애니메이션만 넣고 있음

    if (damage > 0)
        ironclad.play(AnimType::Attack);

    if (defense > 0)
        ironclad.play(AnimType::Defense);
}
