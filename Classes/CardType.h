#pragma once
#include "CardData.h"
#include <vector>
#include "cocos2d.h"

class CardSprite;

enum class EnumType
{
	TypeNone,			// ������
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