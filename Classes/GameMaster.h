#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "CardManager.h"

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

	void createPlayer();
	void setPlayerReady(int index);

	Player * getControlPlayer();

	std::vector<CardData> getDizhuCards() const;

protected:
	CREATE_FUNC(GameMaster);
	virtual bool init() override;

	EnumGameState m_state = EnumGameState::GameInit;

	GameReadyLayer * m_game_ready_layer = nullptr;
	GameLayer * m_game_layer = nullptr;

	//std::vector<Player *> m_players;
	cocos2d::Vector<Player *> m_players;
	int m_control_player = 0;
	std::vector<CardData> m_dizhuCards;

protected:
	void checkState();			// 检查游戏进行状态

	bool isAllPlayerReady();
};