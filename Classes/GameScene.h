#pragma once
#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(GameScene);
	virtual bool init();

	void loadTexture();
};