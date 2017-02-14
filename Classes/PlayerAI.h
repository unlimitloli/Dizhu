#pragma once
#include "Player.h"

class PlayerAI : public Player
{
public:
	static PlayerAI * create(int index);
	virtual bool initPlayer(int index) override;
};