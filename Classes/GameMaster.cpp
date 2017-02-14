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
		break;
	case EnumGameState::GameQiangdizhu:
		break;
	case EnumGameState::GamePlayCard:
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

void GameMaster::createPlayer()
{
	m_players.pushBack(PlayerControl::create(0));
	m_players.pushBack(PlayerAI::create(1));
	m_players.pushBack(PlayerAI::create(2));

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
