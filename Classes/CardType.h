#pragma once
#include "CardData.h"
#include <vector>
#include "cocos2d.h"

class CardSprite;

class CardType
{
public:
	CardType();
	CardType(const std::vector<CardData> &cards);
	CardType(const CardType &card_type);
	CardType(const cocos2d::Vector<CardSprite *> &card_sprites);

	std::vector<CardData> & getCards();

	bool isNone() const;			// Ã»ÓÐ³öÅÆ

protected:
	std::vector<CardData> m_cards;
};

extern CardType NoneCardType;