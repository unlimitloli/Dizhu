#include "GameMaster.h"
#include "GameReadyLayer.h"
#include "GameLayer.h"
#include "PlayerAI.h"
#include "PlayerControl.h"

static GameMaster * master = nullptr;

GameMaster * GameMaster::getInstance()
{
	if (master == nullptr)
		master = GameMaster::create();
	return master;
}

bool GameMaster::init()
{
	if (!Node::init())
		return false;

	return true;
}

void GameMaster::checkState()
{
	switch (m_state)
	{
	case EnumGameState::GameInit:
		m_state = EnumGameState::GameReady;
		startReady();
		checkState();
		break;
	case EnumGameState::GameReady:
		if (isAllPlayerReady())
		{
			m_state = EnumGameState::GameStart;
			checkState();
		}
		break;
	case EnumGameState::GameStart:
		m_state = EnumGameState::GameFlushCard;
		startGame();
		checkState();
		break;
	case EnumGameState::GameFlushCard:
		m_game_layer->showHandCards();
		m_state = EnumGameState::GameQiangdizhu;
		break;
	case EnumGameState::GameQiangdizhu:
		CCLOG("开始抢地主");
		if (m_is_end_dizhu == true)			// 抢地主结束
		{
			m_is_start_dizhu = false;
			m_is_end_dizhu = false;
			m_state = EnumGameState::GamePlayCard;
			checkState();
		}
		else if (m_is_start_dizhu == false)  // 开始抢地主
		{
			m_is_start_dizhu = true;
			m_is_end_dizhu = false;
			m_dizhu_player = m_start_dizhu_player;
			m_cur_dizhu_player = m_start_dizhu_player;
			playerStartQiangdizhu();
		}
		else if (m_cur_dizhu_player == m_start_dizhu_player)
		{
			// 一轮抢地主完成
			m_is_end_dizhu = true;
			m_state = EnumGameState::GamePlayCard;
			if (m_dizhu_player != m_start_dizhu_player)
			{
				playerStartQiangdizhu();
			}
			else
			{
				checkState();
			}
		}
		else
		{
			playerStartQiangdizhu();
		}  
		break;
	case EnumGameState::GamePlayCard:
		CCLOG("开始出牌，地主为: %d", m_dizhu_player);
		startPlayCard();
		break;
	default:
		break;
	}
}

bool GameMaster::isAllPlayerReady()
{
	bool is_all_ready = true;
	for (auto player : m_players)
	{
		if (!player->getReady())
		{
			is_all_ready = false;
			break;
		}
	}
	return is_all_ready;
}

void GameMaster::setGameReadyLayer(GameReadyLayer * layer)
{
	m_game_ready_layer = layer;
}

void GameMaster::setGameLayer(GameLayer * layer)
{
	m_game_layer = layer;
}

void GameMaster::start()
{
	checkState();
}

void GameMaster::startReady()
{
	m_game_layer->setReady();
	m_game_ready_layer->setReady();

	createPlayer();
}

void GameMaster::startGame()
{
	m_game_ready_layer->setVisible(false);
	m_game_layer->setStart();

	CardManager manager;
	manager.flushCard();
	m_dizhuCards = manager.dealCards(m_players);
}

void GameMaster::startQiangdizhu()
{
	m_state = EnumGameState::GameQiangdizhu;
	m_is_start_dizhu = false;
	checkState();
}

void GameMaster::startPlayCard()
{
	// 将地主牌添加到玩家手牌中
	for (auto card : m_dizhuCards)
	{
		m_players.at(m_dizhu_player)->addCard(card);
	}
	m_game_layer->startPlayCard();
}

void GameMaster::playerSureQiangdizhu(int index, bool sure)
{
	if (true == sure)
		m_dizhu_player = index;
	m_cur_dizhu_player = (m_cur_dizhu_player + 1) % 3;
	checkState();
}

void GameMaster::playerStartQiangdizhu()
{
	m_players.at(m_cur_dizhu_player)->startQiangdizhu();
}

void GameMaster::controlPlayerQiangdizhu()
{
	if (m_dizhu_player == m_control_player)		// 叫地主
	{
		m_game_layer->showQiangdizhu(true);
	}
	else											// 抢地主
	{
		m_game_layer->showQiangdizhu(false);
	}

}

void GameMaster::createPlayer()
{
	m_players.pushBack(PlayerControl::create(0));
	m_players.pushBack(PlayerAI::create(1));
	m_players.pushBack(PlayerAI::create(2));

	m_players.at(0)->setControl(m_game_layer);

	m_control_player = 0;
}

void GameMaster::setPlayerReady(int index)
{
	m_game_ready_layer->setPlayerReady(index);
	checkState();
}

Player * GameMaster::getControlPlayer()
{
	return m_players.at(m_control_player);
}

std::vector<CardData> GameMaster::getDizhuCards() const
{
	return m_dizhuCards;
}

void GameMaster::onExit()
{
	Node::onExit();

	master = nullptr;
}
