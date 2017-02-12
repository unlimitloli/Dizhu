#include "GameReadyLayer.h"

#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;

bool GameReadyLayer::init()
{
	if (!Layer::init())
		return false;

	auto csbItem = CSLoader::createNode(csb.game_ready_layer);
	addChild(csbItem);
	root = csbItem->getChildByName("root");

	return true;
}