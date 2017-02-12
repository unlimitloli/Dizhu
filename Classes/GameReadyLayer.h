#pragma once
#include "cocos2d.h"
#include "csb_config.h"

class GameReadyLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameReadyLayer);
	virtual bool init() override;

protected:
	cocos2d::Node * root;
};