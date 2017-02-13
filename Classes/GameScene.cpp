#pragma once
#include "GameScene.h"
#include "GameReadyLayer.h"
#include "GameLayer.h"
#include "GameMaster.h"

USING_NS_CC;

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	addChild(_game);

	auto game_layer = GameLayer::create();
	addChild(game_layer);

	auto game_ready_layer = GameReadyLayer::create();
	addChild(game_ready_layer);

	loadTexture();

	_game->start();

	return true;
}

void GameScene::loadTexture()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cards.plist", "cards.png");
}

