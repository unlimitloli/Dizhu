#pragma once
#include "CardData.h"
#include <vector>

class Player
{
public:
	Player(int index);							// Íæ¼Ò±àºÅ

	void addCard(const CardData &data);			// Ìí¼ÓÊÖÅÆ

protected:
	std::vector<CardData> m_cards;
	int m_index = 0;
};