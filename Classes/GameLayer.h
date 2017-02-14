#pragma once
#include "cocos2d.h"
#include "utils.h"
#include "CardData.h"
#include "CardSprite.h"
#include "ui\CocosGUI.h"

class GameLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init() override;

	void setReady();			// ���õȴ����״̬

	void setStart();
	void showDizhuCards();		// ��ʾ��������
	void showHandCards();		// ��ʾ����

	void showQiangdizhu(bool isDizhu);	// 
	void hideQiangdizhu();

	void addCardToHand(const CardData &data);
	void flushHandCard();

protected:
	cocos2d::Node * m_root;
	cocos2d::Vector<CardSprite *> m_hand_cards;

	cocos2d::ui::Layout *m_panel_self;		// ������

	bool m_is_new_game = true;
};