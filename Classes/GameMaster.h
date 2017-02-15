#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "CardManager.h"
#include "CardType.h"

#define _game		GameMaster::getInstance()

class GameReadyLayer;
class GameLayer;

enum class EnumGameState
{
	GameInit,			// 初始化
	GameReady,			// 准备阶段，等待玩家准备完成
	GameStart,			// 所有玩家准备完成，开始游戏
	GameFlushCard,		// 洗牌，给玩家发牌
	GameQiangdizhu,		// 抢地主
	GamePlayCard,		// 轮流出牌
};

class GameMaster : public cocos2d::Node
{
public:
	static GameMaster * getInstance();

	void setGameReadyLayer(GameReadyLayer *layer);
	void setGameLayer(GameLayer *layer);

	void start();					// 开始游戏
	void startReady();				// 等待玩家准备
	void startGame();				// 开始游戏，进入发牌阶段
	void startQiangdizhu();

	void startPlayCard();

	void playerSureQiangdizhu(int index, bool sure);
	void playerStartQiangdizhu();	// 玩家index抢地主
	void controlPlayerQiangdizhu();	// 控制的玩家抢地主

	void createPlayer();
	void setPlayerReady(int index);

	Player * getControlPlayer();
	Player * getPlayer(int index);

	std::vector<CardData> getDizhuCards() const;

	void playerPlayCard(int index, CardType &card_type);

	virtual void onExit() override;

protected:
	CREATE_FUNC(GameMaster);
	virtual bool init() override;

	EnumGameState m_state = EnumGameState::GameInit;

	GameReadyLayer * m_game_ready_layer = nullptr;
	GameLayer * m_game_layer = nullptr;

	//std::vector<Player *> m_players;
	cocos2d::Vector<Player *> m_players;
	int m_control_player = 0;

	bool m_is_start_dizhu = false;
	bool m_is_end_dizhu = false;
	int m_start_dizhu_player = 0;		// 从此号玩家开始抢地主
	int m_cur_dizhu_player = 0;
	int m_dizhu_player = 0;				// 地主
	std::vector<CardData> m_dizhuCards;

	int m_cur_play_card_palyer = 0;		// 当前出牌的玩家

	CardType m_last_card = NoneCardType;

protected:
	void checkState();			// 检查游戏进行状态

	bool isAllPlayerReady();
};