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
	m_cards.push_back(data);
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

void Player::sortCard()
{
	std::sort(m_cards.begin(), m_cards.end(), std::greater<CardData>());
}

void Player::sureQiangdizhu(bool sure)
{
	_game->playerSureQiangdizhu(m_index, sure);
}
