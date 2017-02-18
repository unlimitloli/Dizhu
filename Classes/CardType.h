#pragma once
#include "CardData.h"
#include <vector>
#include "cocos2d.h"

class CardSprite;

enum class EnumType
{
	TypeNone,			// 不出牌
	TypeVaild,			// 无效
	TypeOne,			// 单牌
	TypeTwo,			// 对子
	TypeThree,			// 三个
	TypeBoom,			// 炸弹
	TypeKingBoom,		// 王炸
	TypeStraight,		// 顺子
	TypeMuiltPair,		// 连对
};

class CardType
{
public:
	CardType();
	CardType(const std::vector<CardData> &cards);
	CardType(const CardType &card_type);
	CardType(const cocos2d::Vector<CardSprite *> &card_sprites);

	std::vector<CardData> & getCards();

	bool isNone() const;			// 没有出牌
	bool isVaild() const;			// 无效牌

	bool winCard(const CardType &card_type) const;		// 是否能大过上家
	int getCompareNum() const;
	EnumType getType() const;

protected:
	std::vector<CardData> m_cards;

	EnumType m_type = EnumType::TypeVaild;
	int m_num = 0;
	int m_length = 0;
	int m_card_count = 0;

protected:
	void checkCardType();
};

extern CardType NoneCardType;