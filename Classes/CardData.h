#pragma once

// ���Ƶ���
enum class EnumCardNum
{
	Card0 = 0,			//��Ч
	Card3 = 3,
	Card4,
	Card5,
	Card6,
	Card7,
	Card8,
	Card9,
	Card10,
	CardJ,
	CardQ,
	CardK,
	CardA,
	Card2,
	CardJoker,
	CardJokerKing,
};

// ��ɫ
enum class EnumCardType
{
	CardTypeNone,			// ��Ч
	CardTypeSpade = 1,		//����
	CardTypeHeart,			//����
	CardTypeDimond,			//����
	CardTypeClub,			//÷��
};

class CardData
{
public:
	CardData();
	CardData(EnumCardNum num, EnumCardType type);
	CardData(const CardData &data);
	int getNum() const;
	int getType() const;

	bool isVaild() const;
	bool operator == (const CardData &data) const;
	bool operator < (const CardData &data) const;
	bool operator > (const CardData &data) const;
protected:
	EnumCardNum m_num = EnumCardNum::Card0;
	EnumCardType m_type = EnumCardType::CardTypeNone;
};