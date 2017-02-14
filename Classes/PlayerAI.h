#pragma once
#include "Player.h"

class PlayerAI : public Player
{
public:
	static PlayerAI * create(int index);
	virtual bool initPlayer(int index) override;
	virtual void startQiangdizhu() override;			// 开始抢地主
};