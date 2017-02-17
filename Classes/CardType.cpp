#include "CardType.h"
#include "CardSprite.h"
#include <algorithm>

using namespace std;

CardType NoneCardType = CardType();			// ²»³öÅÆ

CardType::CardType()
{

}

CardType::CardType(const std::vector<CardData> &cards) : m_cards(cards)
{
	sort(m_cards.begin(), m_cards.end(), std::greater<CardData>());
}

CardType::CardType(const CardType &card_type) : m_cards(card_type.m_cards)
{
	sort(m_cards.begin(), m_cards.end(), std::greater<CardData>());
}

CardType::CardType(const cocos2d::Vector<CardSprite*>& card_sprites)
{
	for (auto sprite : card_sprites)
	{
		m_cards.push_back(sprite->getCardData());
	}
	sort(m_cards.begin(), m_cards.end(), std::greater<CardData>());
}

std::vector<CardData> & CardType::getCards()
{
	return m_cards;
}

bool CardType::isNone() const
{
	return (m_cards.size() == 0);
}
