#include "CardType.h"
#include "CardSprite.h"
#include <algorithm>

using namespace std;

CardType NoneCardType = CardType();			// ������

CardType::CardType()
{
	checkCardType();
}

CardType::CardType(const std::vector<CardData> &cards) : m_cards(cards)
{
	sort(m_cards.begin(), m_cards.end(), std::greater<CardData>());
	checkCardType();
}

CardType::CardType(const CardType &card_type) : m_cards(card_type.m_cards)
{
	sort(m_cards.begin(), m_cards.end(), std::greater<CardData>());
	checkCardType();
}

CardType::CardType(const cocos2d::Vector<CardSprite*>& card_sprites)
{
	for (auto sprite : card_sprites)
	{
		m_cards.push_back(sprite->getCardData());
	}
	sort(m_cards.begin(), m_cards.end(), std::greater<CardData>());
	checkCardType();
}

std::vector<CardData> & CardType::getCards()
{
	return m_cards;
}

bool CardType::isNone() const
{
	return (m_cards.size() == 0);
}

bool CardType::isVaild() const
{
	return true;
}

bool CardType::winCard(const CardType &card_type) const
{
	return true;
}

void CardType::checkCardType()
{
	int card_num[18];
	memset(card_num, 0, sizeof(int) * 18);

	m_card_count = m_cards.size();
	if (m_card_count == 0)
		m_type = EnumType::TypeVaild;

	for (auto & card : m_cards)
	{
		int n = card.getNum();
		++card_num[n];
	}

	int card_count[4] = { 0, 0, 0, 0 };
	int straight_length = 0;	// ˳�ӳ���
	int straight_min_num = 0;	// ˳�ӵ���С�Ƶ���1
	int straight_type = 0;		// ˳������
	int max_straight_length = 0;		// ��󳤶�˳��
	int max_straight_min_num = 0;
	int max_straignt_type = 0;

	for (int i = 0; i < 18; ++i)
	{
		int num = card_num[i];
		if (num == 0)
		{
			straight_length = 0;
			straight_min_num = 0;
			straight_length = 0;
		}
		else
		{
			++card_count[num - 1];
			if (straight_length == 0)		// ��ʼ����˳��
			{
				straight_length = 1;
				straight_min_num = i;
				straight_type = num;
			}
			else
			{
				if (straight_type == num)
				{
					++straight_length;
				}
				else
				{
					straight_length = 0;
					straight_min_num = 0;
					straight_type = 0;
				}
			}
			if (straight_length > max_straight_length)
			{
				max_straight_length = straight_length;
				max_straight_min_num = straight_min_num;
				max_straignt_type = straight_type;
			}
		}
	}

	m_num = max_straight_min_num;			// �Ƚ�ֵ
	m_length = max_straight_length;			// ˳�ӳ���

	if ((card_count[0] == 1) && (card_count[1] == 0) && (card_count[2] == 0) && (card_count[3] == 0))		// ����
	{
		m_type = EnumType::TypeOne;
	}
	else if ((card_count[0] == 2) && (card_count[1] == 0) && (card_count[2] == 0) && (card_count[3] == 0))		// ��ը
	{
		if ((card_num[16] == 1) && (card_num[17] == 1))
			m_type = EnumType::TypeKingBoom;
		else
			m_type = EnumType::TypeVaild;
	}
	else if ((card_count[0] == 0) && (card_count[1] == 1) && (card_count[2] == 0) && (card_count[3] == 0))		// ����
	{
		m_type = EnumType::TypeTwo;
	}
	else
	{
		if ((card_count[0] >= 5) && (card_count[1] == 0) && (card_count[2] == 0) && (card_count[3] == 0))		// ˳��
		{
			if (card_count[0] == max_straight_length)
				m_type = EnumType::TypeStraight;
			else
				m_type = EnumType::TypeVaild;
		}
		else if ((card_count[0] == 0) && (card_count[1] >= 3) && (card_count[2] == 0) && (card_count[3] == 0))		// ����
		{
			if (card_count[1] == max_straight_length)
				m_type = EnumType::TypeMuiltPair;
			else
				m_type = EnumType::TypeVaild;
		}
		else if ((card_count[2] >= 1) && (card_count[3] == 0))			// �ɻ�
		{
			if ((card_count[0] > 0) && (card_count[1] > 0))
				m_type = EnumType::TypeVaild;
			else
			{
				int max_count = std::max(card_count[0], card_count[1]);
				if ((card_count[2] == max_straight_length) && ((max_count == 0) || (card_count[2] == max_count)))
					m_type = EnumType::TypeThree;
				else
					m_type = EnumType::TypeVaild;
			}
		}
		else if ((card_count[0] == 0) && (card_count[1] == 0) && (card_count[2] == 0) && (card_count[3] == 1))		// ը��
		{
			m_type = EnumType::TypeBoom;
		}
		else
			m_type = EnumType::TypeVaild;
	}
}
