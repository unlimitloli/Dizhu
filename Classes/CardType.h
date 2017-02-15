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

	bool isNone() const;			// û�г���

protected:
	std::vector<CardData> m_cards;
};

extern CardType NoneCardType;