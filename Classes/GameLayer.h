#pragma once
#include "cocos2d.h"
#include "utils.h"

class GameLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init() override;

	void setReady();			// 设置等待玩家状态
	void showDizhuCards();		// 显示地主的牌

protected:
	cocos2d::Node * m_root;
};