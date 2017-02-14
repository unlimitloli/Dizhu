#pragma once
#include "CardData.h"
#include <vector>
#include "cocos2d.h"

class GameLayer;

class Player : public cocos2d::Node
{
public:
	// static Player * create(int index);			// ��ұ��
	virtual bool initPlayer(int index);				

	void addCard(const CardData &data);			// �������
	std::vector<CardData>& getHandCard();

	virtual void setControl(GameLayer *game_layer);

	virtual void setReady();					// ����׼�����״̬
	virtual bool getReady();

	virtual void startQiangdizhu() = 0;			// ��ʼ������
	virtual void sureQiangdizhu(bool sure);		// ȷ���Ƿ�������

	virtual void sortCard();

protected:
	std::vector<CardData> m_cards;
	int m_index = 0;
	bool m_is_ready = false;

	GameLayer *m_game_layer = nullptr;
};