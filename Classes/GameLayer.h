#pragma once
#include "cocos2d.h"
#include "utils.h"
#include "CardData.h"
#include "CardSprite.h"
#include "ui\CocosGUI.h"
#include "CardType.h"

class Player;

class GameLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init() override;

	void setReady();			// ���õȴ����״̬

	void setStart(Player *player);
	void showDizhuCards();		// ��ʾ��������
	void showHandCards();		// ��ʾ����

	void showQiangdizhu(bool isDizhu);	// 
	void hideQiangdizhu();

	void startPlayCard();

	void addCardToHand(const CardData &data);
	void flushHandCard();

	void updatePlayerCardNum();

	void showPlayCardButton(bool is_show);		// ��ʾ���ư�ť

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;

	void onTouchButtonPlay(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);		// ����
	void onTouchButtonSkip(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);		// ����
	void onTouchButtonTip(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);		// ��ʾ
	void onTouchButtonReset(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);		// ��ѡ

	void showPlayCard(int player, CardType &card_type);
	void removePlayerPlayeCard(int player);
	void clearPlayerPlayCard();

protected:
	cocos2d::Node * m_root;
	cocos2d::Vector<CardSprite *> m_hand_cards;

	cocos2d::ui::Layout *m_panel_self;		// ������
	cocos2d::ui::Layout *m_panel_out;		// ������
	cocos2d::ui::Layout *m_panel_game;
	cocos2d::Vector<CardSprite *> m_select_cards;

	cocos2d::Vector<CardSprite *> m_card_others[2];		//������ҳ�����

	Player *m_player;

	bool m_is_new_game = true;
};