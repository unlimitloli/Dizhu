#pragma once
#include "Player.h"
#include "GameLayer.h"

class PlayerControl : public Player
{
public:
	static PlayerControl * create(int index);

	virtual void startQiangdizhu() override;			// 开始抢地主
};