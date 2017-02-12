#pragma once

#define _sceneManager		SceneManager::getInstance()

enum class EnumScene
{
	HelloScene,
	StartScene,
	GameScene,
};

class SceneManager
{
public:
	static SceneManager * getInstance();

	void runScene();
	void replaceScene(EnumScene sceneType);
};