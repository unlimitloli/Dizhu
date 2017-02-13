#include "Player.h"

using namespace std;

Player::Player(int index) : m_index(index)
{
}

void Player::addCard(const CardData &data)
{
	m_cards.push_back(data);
}
