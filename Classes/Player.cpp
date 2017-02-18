#include "Player.h"
#include "GameMaster.h"
#include <algorithm>

using namespace std;

bool Player::initPlayer(int index)
{
	m_index = index;
	return true;
}

void Player::addCard(const CardData &data)
{
	// 按从大到小的顺序插入
	size_t index = 0;			// 插入位置
	for (index = 0; index < m_cards.size(); ++index)
	{
		if (data.orderGreater(m_cards.at(index)))
		{
			break;
		}
	}
	m_cards.insert(m_cards.begin() + index, data);
}

std::vector<CardData>& Player::getHandCard()
{
	return m_cards;
}

void Player::setControl(GameLayer * game_layer)
{
	m_game_layer = game_layer;
}

void Player::setReady()
{
	m_is_ready = true;
	_game->setPlayerReady(m_index);
}

bool Player::getReady()
{
	return m_is_ready;
}

void Player::sureQiangdizhu(bool sure)
{
	if (m_is_qiangdizhu == true)
	{
		m_is_qiangdizhu = sure;
		_game->playerSureQiangdizhu(m_index, sure);
	}
	else
	{	
		_game->playerSureQiangdizhu(m_index, false);
	}
}

int Player::getHandCardNum() const
{
	return m_cards.size();
}

void Player::setDizhu(bool dizhu)
{
	m_is_dizhu = dizhu;
}

bool Player::isDizhu() const
{
	return m_is_dizhu;
}

void Player::startPlayCard(CardType &last_card)
{
	m_last_card = last_card;
	resetCardNum();

	onStartPlayCard();
}

bool Player::playCard(CardType &card_type)
{
	if (card_type.winCard(m_last_card))
	{
		// 从手牌移除出的牌
		auto &out_cards = card_type.getCards();
		auto it = remove_if(m_cards.begin(), m_cards.end(), [&](const CardData &data) {
			return (find(out_cards.begin(), out_cards.end(), data) != out_cards.end());
		});
		m_cards.erase(it, m_cards.end());

		_game->playerPlayCard(m_index, card_type);

		onPlayCard();
		return true;
	}
	
	return false;
}

CardType Player::getTip() const
{
	vector<CardData> card_datas;
	switch (m_last_card.getType())
	{
	case EnumType::TypeNone:
		card_datas = findCard(1, 0, 1);
		break;
	case EnumType::TypeOne:
		card_datas = findCard(1, m_last_card.getCompareNum(), 1);
		break;
	case EnumType::TypeTwo:
		card_datas = findCard(2, m_last_card.getCompareNum(), 1);
		break;
	default:
		break;
	}

	return CardType(card_datas);
}

void Player::resetCardNum()
{
	memset(m_card_num, 0, sizeof(int) * 18);
	for (auto & card : m_cards)
	{
		int n = card.getNum();
		++m_card_num[n];
	}
}

std::vector<CardData> Player::findCard(int type, int min_num, int count) const
{
	vector<CardData> card_datas;

	int index = 0;
	int have_count = 0;
	for (int i = min_num + 1; i < 18; ++i)
	{
		if (m_card_num[i] >= type)
		{
			++have_count;
			if (have_count == 1)
			{
				index = i;
			}
			if (have_count == count)
				break;
		}
		else
			have_count = 0;
	}

	if (have_count == count)		// 有查找的牌
	{
		int card_index = 0;
		for (int i = 0; i < index; ++i)		// 计算寻找的牌在牌组中的下标
		{
			card_index += m_card_num[i];
		}
		for (int i = 0; i < type * count; ++i)
		{
			card_datas.push_back(m_cards.at(m_cards.size() - card_index - i - 1));
		}
	}

	return card_datas;
}
