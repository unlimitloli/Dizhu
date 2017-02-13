#pragma once
#include "CardData.h"
#include <vector>
#include "Player.h"

class CardManager
{
public:
	void flushCard();		// 洗牌，创建54张卡牌
	std::vector<CardData> dealCards(std::vector<Player *> players);			// 给玩家发牌，返回地主的3张牌

protected:
	std::vector<CardData> m_cards;
};