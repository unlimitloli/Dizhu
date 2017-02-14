#include "CardManager.h"
#include <time.h>

using namespace std;

const int CARD_COUNT = 54;

void CardManager::flushCard()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	m_cards.clear();
	m_cards.resize(CARD_COUNT);

	for (int i = 3; i <= 17; ++i)
	{
		for (int j = 1; j <= 4; ++j)
		{
			if (i >= 16 && j > 1)
				continue;

			int index = 0;
			do
			{
				index = rand() % CARD_COUNT;
			} while (!m_cards[index].isVaild());
			m_cards[index] = CardData(i, j);
		}
	}
}

std::vector<CardData> CardManager::dealCards(cocos2d::Vector<Player *> players)
{
	// √ø»À17’≈≈∆
	for (int i = 0; i < 17; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			players.at(j)->addCard(m_cards.back());
			m_cards.pop_back();
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		players.at(i)->sortCard();
	}
	return m_cards;
}