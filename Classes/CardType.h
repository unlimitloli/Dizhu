#pragma once
#include "CardData.h"
#include <vector>

class CardType
{
public:
	CardType();
	CardType(const std::vector<CardData> &cards);
	CardType(const CardType &card_type);

	std::vector<CardData> & getCards();

	bool isNone() const;			// Ã»ÓÐ³öÅÆ

protected:
	std::vector<CardData> m_cards;
};

extern CardType NoneCardType;