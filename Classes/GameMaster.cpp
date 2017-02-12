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
