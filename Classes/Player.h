#pragma once
#include "CardData.h"
#include <vector>

class Player
{
public:
	Player(int index);							// ��ұ��

	void addCard(const CardData &data);			// �������

protected:
	std::vector<CardData> m_cards;
	int m_index = 0;
};