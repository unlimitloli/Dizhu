#include "CardType.h"
#include "CardSprite.h"

using namespace std;

CardType NoneCardType = CardType();			// ²»³öÅÆ

CardType::CardType()
{

}

CardType::CardType(const std::vector<CardData> &cards) : m_cards(cards)
{

}

CardType::CardType(const CardType &card_type) : m_cards(card_type.m_cards)
{

}

CardType::CardType(const cocos2d::Vector<CardSprite*>& card_sprites)
{
	for (auto sprite : card_sprites)
	{
		m_cards.push_back(sprite->getCardData());
	}
}

std::vector<CardData> & CardType::getCards()
{
	return m_cards;
}

bool CardType::isNone() const
{
	return (m_cards.size() == 0);
}
