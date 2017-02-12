#pragma once
#include "cocos2d.h"
#include "csb_config.h"

class GameLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init() override;

protected:
	cocos2d::Node * root;
};