#include "CardSprite.h"

USING_NS_CC;
using namespace std;

CardSprite * CardSprite::create(const CardData &data)
{
	auto card = new CardSprite();
	if (card != nullptr && card->initWithData(data))
	{
		card->autorelease();
		return card;
	}
	CC_SAFE_DELETE(card);
	return nullptr;
}

CardSprite * CardSprite::create(int num, int type)
{
	auto data = CardData((EnumCardNum)num, (EnumCardType)type);
	return create(data);
}

bool CardSprite::initWithData(const CardData &data)
{
	string filename = StringUtils::format("card%d_%d.png", data.getNum(), data.getType());
	if (!Sprite::initWithSpriteFrameName(filename))
		return false;

	return true;
}