#pragma once
#include "GameScene.h"
#include "GameReadyLayer.h"
#include "GameLayer.h"

USING_NS_CC;

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	auto game_layer = GameLayer::create();
	addChild(game_layer);

	auto game_ready_layer = GameReadyLayer::create();
	addChild(game_ready_layer);

	return true;
}
