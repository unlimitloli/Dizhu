#include "CardType.h"
#include "CardSprite.h"
#include <algorithm>

using namespace std;

CardType NoneCardType = CardType();			// 不出牌

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
	if (m_type == EnumType::TypeNone)
		return true;
	return false;
}

bool CardType::isVaild() const
{
	if (m_type == EnumType::TypeVaild)
		return true;
	return false;
}

int CardType::getCompareNum() const
{
	return m_num;
}

bool CardType::winCard(const CardType &card_type) const
{
	if (isVaild())
		return false;

	if (card_type.isVaild())
		return true;

	if (card_type.isNone())				// 上家没又出牌，即玩家必须出牌
	{
		if (isNone())
			return false;
		return true;
	}
	else
	{
		if (isNone())					// 可以选择不出牌
			return true;
		else
		{
			if ((m_type == card_type.m_type) && (m_length == card_type.m_length) &&
				(m_card_count == card_type.m_card_count) && (m_num > card_type.m_num))
				return true;
			else
				return false;
		}
	}

	return false;
}

void CardType::checkCardType()
{
	int card_num[18];
	memset(card_num, 0, sizeof(int) * 18);

	m_card_count = m_cards.size();
	if (m_card_count == 0)
	{
		m_type = EnumType::TypeNone;
		return;
	}

	for (auto & card : m_cards)
	{
		int n = card.getNum();
		++card_num[n];
	}

	int card_count[4] = { 0, 0, 0, 0 };
	int straight_length = 0;	// 顺子长度
	int straight_min_num = 0;	// 顺子的最小牌点数1
	int straight_type = 0;		// 顺子类型
	int max_straight_length = 0;		// 最大长度顺子
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
			if (straight_length == 0)		// 开始计数顺子
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

	m_num = max_straight_min_num;			// 比较值
	m_length = max_straight_length;			// 顺子长度

	if ((card_count[0] == 1) && (card_count[1] == 0) && (card_count[2] == 0) && (card_count[3] == 0))		// 单牌
	{
		m_type = EnumType::TypeOne;
	}
	else if ((card_count[0] == 2) && (card_count[1] == 0) && (card_count[2] == 0) && (card_count[3] == 0))		// 王炸
	{
		if ((card_num[16] == 1) && (card_num[17] == 1))
			m_type = EnumType::TypeKingBoom;
		else
			m_type = EnumType::TypeVaild;
	}
	else if ((card_count[0] == 0) && (card_count[1] == 1) && (card_count[2] == 0) && (card_count[3] == 0))		// 对子
	{
		m_type = EnumType::TypeTwo;
	}
	else
	{
		if ((card_count[0] >= 5) && (card_count[1] == 0) && (card_count[2] == 0) && (card_count[3] == 0))		// 顺子
		{
			if (card_count[0] == max_straight_length)
				m_type = EnumType::TypeStraight;
			else
				m_type = EnumType::TypeVaild;
		}
		else if ((card_count[0] == 0) && (card_count[1] >= 3) && (card_count[2] == 0) && (card_count[3] == 0))		// 连对
		{
			if (card_count[1] == max_straight_length)
				m_type = EnumType::TypeMuiltPair;
			else
				m_type = EnumType::TypeVaild;
		}
		else if ((card_count[2] >= 1) && (card_count[3] == 0))			// 飞机
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
		else if ((card_count[0] == 0) && (card_count[1] == 0) && (card_count[2] == 0) && (card_count[3] == 1))		// 炸弹
		{
			m_type = EnumType::TypeBoom;
		}
		else
			m_type = EnumType::TypeVaild;
	}
}

EnumType CardType::getType() const
{
	return m_type;
}
