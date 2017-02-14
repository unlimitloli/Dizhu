#include "GameReadyLayer.h"
#include "GameMaster.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;

bool GameReadyLayer::init()
{
	if (!Layer::init())
		return false;

	_game->setGameReadyLayer(this);

	auto csbItem = CSLoader::createNode(csb.game_ready_layer);
	addChild(csbItem);
	m_root = csbItem->getChildByName("root");

	auto Button_Ready = dynamic_cast<Button *>(getWidgetByName(m_root, "Button_Ready"));
	Button_Ready->addTouchEventListener([&](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		if (cocos2d::ui::Widget::TouchEventType::ENDED == type)
			playerReady();
	});

	return true;
}

void GameReadyLayer::setReady()
{
	auto root = this->m_root;
	for (int i = 0; i < 3; ++i)
	{
		auto Image_Ready = getWidgetByName(root, getNameWithIndex("Image_Ready_%d", i));
		Image_Ready->setVisible(false);
	}
}

void GameReadyLayer::playerReady()
{
	auto player = _game->getControlPlayer();
	player->setReady();
}

void GameReadyLayer::setPlayerReady(int index)
{
	auto Image_Ready = getWidgetByName(this->m_root, getNameWithIndex("Image_Ready_%d", index));
	Image_Ready->setVisible(true);
}
