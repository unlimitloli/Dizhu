#pragma once
#include "Player.h"

class PlayerControl : public Player
{
public:
	static PlayerControl * create(int index);
};