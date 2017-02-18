#pragma once
#include "CardData.h"
#include <vector>
#include "cocos2d.h"

class CardSprite;

enum class EnumType
{
	TypeVaild,			// ��Ч
	TypeOne,			// ����
	TypeTwo,			// ����
	TypeThree,			// ����
	TypeBoom,			// ը��
	TypeKingBoom,		// ��ը
	TypeStraight,		// ˳��
	TypeMuiltPair,		// ����
};

class CardType
{
public:
	CardType();
	CardType(const std::vector<CardData> &cards);
	CardType(const CardType &card_type);
	CardType(const cocos2d::Vector<CardSprite *> &card_sprites);

	std::vector<CardData> & getCards();

	bool isNone() const;			// û�г���
	bool isVaild() const;			// ��Ч��

	bool winCard(const CardType &card_type) const;		// �Ƿ��ܴ���ϼ�

protected:
	std::vector<CardData> m_cards;

	EnumType m_type = EnumType::TypeVaild;
	int m_num;
	int m_length;
	int m_card_count;

protected:
	void checkCardType();
};

extern CardType NoneCardType;