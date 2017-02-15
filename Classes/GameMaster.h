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
	void startQiangdizhu();

	void startPlayCard();

	void playerSureQiangdizhu(int index, bool sure);
	void playerStartQiangdizhu();	// ���index������
	void controlPlayerQiangdizhu();	// ���Ƶ����������

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
	int m_start_dizhu_player = 0;		// �Ӵ˺���ҿ�ʼ������
	int m_cur_dizhu_player = 0;
	int m_dizhu_player = 0;				// ����
	std::vector<CardData> m_dizhuCards;

	int m_cur_play_card_palyer = 0;		// ��ǰ���Ƶ����

	CardType m_last_card = NoneCardType;

protected:
	void checkState();			// �����Ϸ����״̬

	bool isAllPlayerReady();
};