#pragma once
#include "Player.h"

class PlayerControl : public Player
{
public:
	static PlayerControl * create(int index);

	virtual void startQiangdizhu() override;			// ��ʼ������

	virtual void onStartPlayCard() override;
	virtual void onPlayCard() override;
};