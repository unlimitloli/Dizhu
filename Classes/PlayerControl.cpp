#include "PlayerControl.h"
#include "cocos2d.h"
#include "GameMaster.h"
#include "GameLayer.h"

USING_NS_CC;

PlayerControl * PlayerControl::create(int index)
{
	auto player = new PlayerControl();
	if (player != nullptr && player->initPlayer(index))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return false;
}

void PlayerControl::startQiangdizhu()
{
	if (m_is_qiangdizhu == true)
		_game->controlPlayerQiangdizhu();
	else
		sureQiangdizhu(false);
}

void PlayerControl::onStartPlayCard()
{
	m_game_layer->showPlayCardButton(true);
}

void PlayerControl::onPlayCard()
{
	m_game_layer->showPlayCardButton(false);
}
