#include "CardData.h"

CardData::CardData() :
	m_num(EnumCardNum::Card0), m_type(EnumCardType::CardTypeNone)
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

bool CardData::isVaild() const
{
	return (m_num == EnumCardNum::Card0 || m_type == EnumCardType::CardTypeNone);
}

bool CardData::operator== (const CardData &data) const
{
	return (m_num == data.m_num);
}

bool CardData::operator< (const CardData &data) const
{
	return (getNum() < data.getNum());
}

bool CardData::operator> (const CardData &data) const
{
	return (getNum() > data.getNum());
}
