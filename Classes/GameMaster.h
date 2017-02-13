#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "CardManager.h"

#define _game		GameMaster::getInstance()

class GameReadyLayer;
class GameLayer;

class GameMaster : public cocos2d::Node
{
public:
	static GameMaster * getInstance();

	void setGameReadyLayer(GameReadyLayer *layer);
	void setGameLayer(GameLayer *layer);

	void start();					// ��ʼ��Ϸ
	void startReady();				// �ȴ����׼��
	void startGame();				// ��ʼ��Ϸ�����뷢�ƽ׶�

	std::vector<CardData> getDizhuCards() const;

protected:
	CREATE_FUNC(GameMaster);
	virtual bool init() override;

	GameReadyLayer * m_game_ready_layer = nullptr;
	GameLayer * m_game_layer = nullptr;

	std::vector<Player *> m_players;
	std::vector<CardData> m_dizhuCards;
};