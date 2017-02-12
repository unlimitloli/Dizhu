#pragma once
#include "SceneManager.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "StartLayer.h"
#include "GameScene.h"

USING_NS_CC;

static SceneManager * manager = nullptr;

SceneManager * SceneManager::getInstance()
{
	if (manager == nullptr)
		manager = new SceneManager();
	return manager;
}

void SceneManager::runScene()
{
	auto director = Director::getInstance();
	auto scene = StartLayer::createScene();
	director->runWithScene(scene);
}

void SceneManager::replaceScene(EnumScene sceneType)
{
	auto diretcor = Director::getInstance();
	Scene * scene = nullptr;
	switch (sceneType)
	{
	case EnumScene::HelloScene:
		scene = HelloWorld::createScene();
		break;
	case EnumScene::StartScene:
		scene = StartLayer::createScene();
		break;
	case EnumScene::GameScene:
		scene = GameScene::create();
		break;
	default:
		break;
	}
	if (scene != nullptr)
		diretcor->replaceScene(scene);
}