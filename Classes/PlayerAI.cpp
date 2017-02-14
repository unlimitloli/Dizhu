#include "PlayerAI.h"
#include "cocos2d.h"

USING_NS_CC;

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
	sureQiangdizhu(true);
}
