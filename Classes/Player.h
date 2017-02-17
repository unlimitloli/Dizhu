#pragma once
#include "CardData.h"
#include <vector>
#include "cocos2d.h"
#include "CardType.h"

class GameLayer;

class Player : public cocos2d::Node
{
public:
	// static Player * create(int index);			// 玩家编号
	virtual bool initPlayer(int index);				

	void addCard(const CardData &data);			// 添加手牌
	std::vector<CardData>& getHandCard();

	virtual void setControl(GameLayer *game_layer);

	virtual void setReady();					// 设置准备完成状态
	virtual bool getReady();

	virtual void startQiangdizhu() = 0;			// 开始抢地主
	virtual void sureQiangdizhu(bool sure);		// 确定是否抢地主

	int getHandCardNum() const;

	void setDizhu(bool dizhu);
	bool isDizhu() const;

	void startPlayCard(CardType &last_card);
	bool playCard(CardType &card_type);	// 出牌

	virtual void onStartPlayCard() {};
	virtual void onPlayCard() {};

protected:
	std::vector<CardData> m_cards;
	int m_index = 0;
	bool m_is_ready = false;
	bool m_is_dizhu = false;

	bool m_is_qiangdizhu = true;

	GameLayer *m_game_layer = nullptr;
	CardType m_last_card;
};