#pragma once
#include "CardData.h"
#include <vector>
#include "Player.h"

class CardManager
{
public:
	void flushCard();		// ϴ�ƣ�����54�ſ���
	std::vector<CardData> dealCards(std::vector<Player *> players);			// ����ҷ��ƣ����ص�����3����

protected:
	std::vector<CardData> m_cards;
};