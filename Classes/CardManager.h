#pragma once
#include "CardData.h"
#include <vector>
#include "Player.h"
#include "cocos2d.h"

class CardManager
{
public:
	void flushCard();		// ϴ�ƣ�����54�ſ���
	std::vector<CardData> dealCards(cocos2d::Vector<Player *> players);			// ����ҷ��ƣ����ص�����3����

protected:
	std::vector<CardData> m_cards;
};