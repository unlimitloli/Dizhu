#include "GameMaster.h"
#include "GameReadyLayer.h"
#include "GameLayer.h"

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
	startReady();
}

void GameMaster::startReady()
{
	m_game_layer->setReady();
	m_game_ready_layer->setReady();
}

void GameMaster::startGame()
{
	m_players.resize(3);
	m_players[0] = new Player(0);
	m_players[1] = new Player(1);
	m_players[2] = new Player(2);

	CardManager manager;
	manager.flushCard();
	m_dizhuCards = manager.dealCards(m_players);
	m_game_layer->showDizhuCards();
}

std::vector<CardData> GameMaster::getDizhuCards() const
{
	return m_dizhuCards;
}
