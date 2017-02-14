#pragma once
#include "CardData.h"
#include <vector>
#include "cocos2d.h"

class Player : public cocos2d::Node
{
public:
	static Player * create(int index);			// 玩家编号
	virtual bool initPlayer(int index);				

	void addCard(const CardData &data);			// 添加手牌
	std::vector<CardData>& getHandCard();

	virtual void setReady();					// 设置准备完成状态
	virtual bool getReady();

	virtual void sortCard();

protected:
	std::vector<CardData> m_cards;
	int m_index = 0;
	bool m_is_ready = false;
};