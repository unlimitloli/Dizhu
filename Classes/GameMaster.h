#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "CardManager.h"

#define _game		GameMaster::getInstance()

class GameReadyLayer;
class GameLayer;

enum class EnumGameState
{
	GameInit,			// ��ʼ��
	GameReady,			// ׼���׶Σ��ȴ����׼�����
	GameStart,			// �������׼����ɣ���ʼ��Ϸ
	GameFlushCard,		// ϴ�ƣ�����ҷ���
	GameQiangdizhu,		// ������
	GamePlayCard,		// ��������
};

class GameMaster : public cocos2d::Node
{
public:
	static GameMaster * getInstance();

	void setGameReadyLayer(GameReadyLayer *layer);
	void setGameLayer(GameLayer *layer);

	void start();					// ��ʼ��Ϸ
	void startReady();				// �ȴ����׼��
	void startGame();				// ��ʼ��Ϸ�����뷢�ƽ׶�

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
	void checkState();			// �����Ϸ����״̬

	bool isAllPlayerReady();
};