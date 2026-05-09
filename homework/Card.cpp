#include "Card.h"
#include "Player.h"
#include "Enemy.h"

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
    image.drawWidth = 118;
    image.drawHeight = 192;
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
    ironclad->applyCardMp(cost);

    if (damage > 0)
    {
        ironclad->play(AnimType::Attack);

        if (!enemies.empty())
        {
            enemies[0]->play(AnimType::Damaged);
            enemies[0]->damaged(damage);
        }
    }
        

    if (defense > 0)
    {
        ironclad->play(AnimType::Defense);
        ironclad->defense(defense);
    }
}
