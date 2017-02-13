#include "GameLayer.h"
#include "GameMaster.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "CardSprite.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;

bool GameLayer::init()
{
	if (!Layer::init())
		return false;

	_game->setGameLayer(this);

	auto csbItem = CSLoader::createNode(csb.game_layer);
	addChild(csbItem);
	m_root = csbItem->getChildByName("root");

	return true;
}

void GameLayer::setReady()
{
	auto Panel_Game = getWidgetByName(m_root, "Panel_Game");
	//Panel_Game->setVisible(false);
	auto Panel_Self = getWidgetByName(m_root, "Panel_Self");
	auto sprite = CardSprite::create(16, 1);
	sprite->setPosition(100, 100);
	Panel_Self->removeAllChildrenWithCleanup(true);
	Panel_Self->addChild(sprite);
}
