#pragma once
#include "CardData.h"
#include <vector>
#include "cocos2d.h"
#include "CardType.h"

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

	int getHandCardNum() const;

	void setDizhu(bool dizhu);
	bool isDizhu() const;

	void startPlayCard(CardType &last_card);
	bool playCard(CardType &card_type);	// ����

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