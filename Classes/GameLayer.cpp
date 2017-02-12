#include "GameLayer.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;

bool GameLayer::init()
{
	if (!Layer::init())
		return false;

	auto csbItem = CSLoader::createNode(csb.game_layer);
	addChild(csbItem);
	root = csbItem->getChildByName("root");

	return true;
}