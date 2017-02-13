#pragma once
#include "utils.h"
#include "CardData.h"

class CardSprite : public cocos2d::Sprite
{
public:
	static CardSprite * create(const CardData &data);
	static CardSprite * create(int num, int type);
	bool initWithData(const CardData &data);
protected:
	CardData m_data;
};