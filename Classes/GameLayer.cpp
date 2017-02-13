#include "GameLayer.h"
#include "GameMaster.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "CardManager.h"
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
}

void GameLayer::showDizhuCards()
{
	auto dizhuCards = _game->getDizhuCards();
	for (int i = 0; i < 3; ++i)
	{
		auto name = StringUtils::format("Panel_Dizhu_%d", i);
		auto Panel_Dizhu = getWidgetByName(m_root, name);
		auto card = CardSprite::create(dizhuCards[i]);
		Panel_Dizhu->addChild(card);
	}
}
