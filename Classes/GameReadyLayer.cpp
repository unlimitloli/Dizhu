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
	Button_Ready->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		if (cocos2d::ui::Widget::TouchEventType::ENDED == type)
			_game->startGame();
	});

	return true;
}

void GameReadyLayer::setReady()
{
	auto Panel_JiaoDizhu = getWidgetByName(m_root, "Panel_JiaoDizhu");
	auto Panel_QiangDizhu = getWidgetByName(m_root, "Panel_QiangDizhu");

	Panel_JiaoDizhu->setVisible(false);
	Panel_QiangDizhu->setVisible(false);
}
