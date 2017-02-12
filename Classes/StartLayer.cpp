#include "StartLayer.h"
#include "SceneManager.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;

Scene * StartLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = StartLayer::create();
	scene->addChild(layer);
	return scene;
}

bool StartLayer::init()
{
	if (!Layer::init())
		return false;

	auto csbItem = CSLoader::createNode(csb.start_layer);
	addChild(csbItem);
	m_root = csbItem->getChildByName("root");

	auto btnStart = dynamic_cast<Button *>(m_root->getChildByName("Button_Start"));
	btnStart->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		if (Widget::TouchEventType::ENDED == type)
			_sceneManager->replaceScene(EnumScene::GameScene);
	});

	return true;
}
