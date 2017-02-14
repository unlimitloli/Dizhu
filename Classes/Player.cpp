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
