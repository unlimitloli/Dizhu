#pragma once
#include "cocos2d.h"
#include "utils.h"

class GameLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init() override;

	void setReady();			// ÉèÖÃµÈ´ıÍæ¼Ò×´Ì¬

protected:
	cocos2d::Node * m_root;
};