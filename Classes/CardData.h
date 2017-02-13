#pragma once

// 卡牌点数
enum class EnumCardNum
{
	Card0 = 0,			//无效
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

// 花色
enum class EnumCardType
{
	CardTypeNone,			// 无效
	CardTypeSpade = 1,		//黑桃
	CardTypeHeart,			//红桃
	CardTypeDimond,			//方块
	CardTypeClub,			//梅花
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