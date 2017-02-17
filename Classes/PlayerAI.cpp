#include "PlayerAI.h"
#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using namespace std;

PlayerAI * PlayerAI::create(int index)
{
	auto player = new PlayerAI();
	if (player != nullptr && player->initPlayer(index))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

bool PlayerAI::initPlayer(int index)
{
	if (!Player::initPlayer(index))
		return false;

	setReady();
	return true;
}

void PlayerAI::startQiangdizhu()
{
	if (m_is_qiangdizhu == true)
		sureQiangdizhu(true);
	else
		sureQiangdizhu(false);
}

void PlayerAI::onStartPlayCard()
{
	runAction(Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create(CC_CALLBACK_0(PlayerAI::aiPlayerCard, this)),
		nullptr
	));
}

void PlayerAI::aiPlayerCard()
{
	vector<CardData> card_data;
	card_data.push_back(m_cards[1]);
	card_data.push_back(m_cards[2]);
	playCard(CardType(card_data));
}
