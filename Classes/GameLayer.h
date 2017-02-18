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

	void setReady();			// 设置等待玩家状态

	void setStart(Player *player);
	void showDizhuCards();		// 显示地主的牌
	void showHandCards();		// 显示手牌

	void showQiangdizhu(bool isDizhu);	// 
	void hideQiangdizhu();

	void startPlayCard();

	void addCardToHand(const CardData &data);
	void flushHandCard();

	void updatePlayerCardNum();

	void showPlayCardButton(bool is_show);		// 显示出牌按钮

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;

	void onTouchButtonPlay(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);		// 出牌
	void onTouchButtonSkip(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);		// 不出
	void onTouchButtonTip(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);		// 提示
	void onTouchButtonReset(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);		// 重选

	void showPlayCard(int player, CardType &card_type);
	void removePlayerPlayeCard(int player);
	void clearPlayerPlayCard();

protected:
	cocos2d::Node * m_root;
	cocos2d::Vector<CardSprite *> m_hand_cards;

	cocos2d::ui::Layout *m_panel_self;		// 手牌区
	cocos2d::ui::Layout *m_panel_out;		// 出牌区
	cocos2d::ui::Layout *m_panel_game;
	cocos2d::Vector<CardSprite *> m_select_cards;

	cocos2d::Vector<CardSprite *> m_card_others[2];		//其他玩家出的牌

	Player *m_player;

	bool m_is_new_game = true;
};