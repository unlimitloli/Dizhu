#include "CardData.h"

CardData::CardData() :
	m_num(EnumCardNum::Card0), m_type(EnumCardType::CardTypeNone)
{
}

CardData::CardData(int num, int type) :
	CardData(EnumCardNum(num), EnumCardType(type))
{
}

CardData::CardData(EnumCardNum num, EnumCardType type) :
	m_num(num), m_type(type)
{
}

CardData::CardData(const CardData &data):
	m_num(data.m_num), m_type(data.m_type)
{
}

int CardData::getNum() const
{
	return (int)m_num;
}

int CardData::getType() const
{
	return (int)m_type;
}

bool CardData::orderGreater(const CardData & data) const
{
	if (getNum() > data.getNum())
		return true;
	else if ((getNum() == data.getNum()) && (getType() < data.getType()))
		return true;
	else
		return false;
}

bool CardData::isVaild() const
{
	if (m_num < EnumCardNum::Card3 || m_num > EnumCardNum::CardJokerKing)
		return true;
	if (m_num == EnumCardNum::CardJoker || m_num == EnumCardNum::CardJokerKing)
	{
		if (m_type != EnumCardType::CardTypeSpade)
			return true;
	}
	return false;
}

bool CardData::operator== (const CardData &data) const
{
	return (m_num == data.m_num) && (m_type == data.m_type);
}

bool CardData::operator< (const CardData &data) const
{
	return (getNum() < data.getNum());
}

bool CardData::operator> (const CardData &data) const
{
	return (getNum() > data.getNum());
}
