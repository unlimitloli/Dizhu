#pragma once
#include "Player.h"

class PlayerControl : public Player
{
public:
	static PlayerControl * create(int index);

	virtual void startQiangdizhu() override;			// 开始抢地主

	virtual void onStartPlayCard() override;
	virtual void onPlayCard() override;
};