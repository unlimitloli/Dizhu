#include "Player.h"
#include "GameMaster.h"
#include <algorithm>

using namespace std;

Player * Player::create(int index)
{
	auto player = new Player();
	if (player != nullptr && player->initPlayer(index))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

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
