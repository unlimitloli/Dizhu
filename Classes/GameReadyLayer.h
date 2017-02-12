#pragma once
#include "cocos2d.h"
#include "utils.h"

class GameReadyLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameReadyLayer);
	virtual bool init() override;

	void setReady();			// ���õȴ����״̬

protected:
	cocos2d::Node * m_root;
};