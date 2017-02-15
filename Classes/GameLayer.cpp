#include "GameLayer.h"
#include "GameMaster.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "CardManager.h"
#include "CardSprite.h"
#include "SceneManager.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;

const int CARD_WIDTH = 72;
const int CARD_HEIGHT = 108;

bool GameLayer::init()
{
	if (!Layer::init())
		return false;

	_game->setGameLayer(this);

	auto csbItem = CSLoader::createNode(csb.game_layer);
	addChild(csbItem);
	m_root = csbItem->getChildByName("root");

	m_panel_self = dynamic_cast<Layout *>(getWidgetByName(m_root, "Panel_Self"));

	auto btnExit = dynamic_cast<Button *>(getWidgetByName(m_root, "Button_Exit"));
	btnExit->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::ENDED == type)
		{
			_sceneManager->replaceScene(EnumScene::StartScene);
		}
	});

	return true;
}

void GameLayer::setReady()
{
	auto Panel_Game = getWidgetByName(m_root, "Panel_Game");
	Panel_Game->setVisible(false);
}

void GameLayer::setStart()
{
	auto Panel_Game = getWidgetByName(m_root, "Panel_Game");
	Panel_Game->setVisible(true);

	auto Panel_QiangDizhu = getWidgetByName(m_root, "Panel_QiangDizhu");
	auto Panel_JiaoDizhu = getWidgetByName(m_root, "Panel_JiaoDizhu");
	auto Panel_Buyao = getWidgetByName(m_root, "Panel_Buyao");
	auto Panel_Button = getWidgetByName(m_root, "Panel_Button");

	Panel_QiangDizhu->setVisible(false);
	Panel_JiaoDizhu->setVisible(false);
	Panel_Buyao->setVisible(false);
	Panel_Button->setVisible(false);
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
	updatePlayerCardNum();
	_game->startQiangdizhu();
}

void GameLayer::showHandCards()
{
	auto player = _game->getControlPlayer();
	auto &cards = player->getHandCard();

	int count = cards.size();

	auto callback = [&, count]()
	{
		static int index = 0;
		if (m_is_new_game)
		{
			index = 0;
			m_is_new_game = false;
		}

		if (index < count)
		{
			addCardToHand(cards.at(index));
			++index;
		}
	};

	auto action = Sequence::create(Repeat::create(Sequence::create(
		CallFunc::create(callback),
		DelayTime::create(0.3f),
		nullptr),
		count),
		CallFunc::create(CC_CALLBACK_0(GameLayer::showDizhuCards, this)),
		nullptr);

	runAction(action);
}

void GameLayer::addCardToHand(const CardData &data)
{
	auto sprite = CardSprite::create(data);

	int count = m_hand_cards.size();
	Size size = sprite->getContentSize();

	sprite->setPosition(count * CARD_WIDTH / 2, 0);
	m_panel_self->addChild(sprite);
	m_hand_cards.pushBack(sprite);
	m_panel_self->setContentSize(Size((count + 1) * CARD_WIDTH / 2, CARD_HEIGHT));
}

void GameLayer::showQiangdizhu(bool isDizhu)
{
	Button *btnSure = nullptr;
	Button *btnCancel = nullptr;
	if (true == isDizhu)		// 显示叫地主
	{
		auto Panel_JiaoDizhu = getWidgetByName(m_root, "Panel_JiaoDizhu");
		Panel_JiaoDizhu->setVisible(true);
		btnSure = dynamic_cast<Button *>(Panel_JiaoDizhu->getChildByName("Button_JiaoDizhu"));
		btnCancel = dynamic_cast<Button *>(Panel_JiaoDizhu->getChildByName("Button_BujiaoDizhu"));
	}
	else						// 显示抢地主
	{
		auto Panel_QiangDizhu = getWidgetByName(m_root, "Panel_QiangDizhu");
		Panel_QiangDizhu->setVisible(true);
		btnSure = dynamic_cast<Button *>(Panel_QiangDizhu->getChildByName("Button_QiangDizhu"));
		btnCancel = dynamic_cast<Button *>(Panel_QiangDizhu->getChildByName("Button_BuqiangDizhu"));
	}

	btnSure->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::ENDED == type)
		{
			hideQiangdizhu();
			_game->getControlPlayer()->sureQiangdizhu(true);
		}
	});

	btnCancel->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::ENDED == type)
		{
			hideQiangdizhu();
			_game->getControlPlayer()->sureQiangdizhu(false);
		}
	});
}

void GameLayer::hideQiangdizhu()
{
	auto Panel_QiangDizhu = getWidgetByName(m_root, "Panel_QiangDizhu");
	auto Panel_JiaoDizhu = getWidgetByName(m_root, "Panel_JiaoDizhu");

	Panel_QiangDizhu->setVisible(false);
	Panel_JiaoDizhu->setVisible(false);
}

void GameLayer::startPlayCard()
{
	flushHandCard();
	updatePlayerCardNum();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

	m_panel_self->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, m_panel_self);
}

void GameLayer::flushHandCard()
{
	auto &cards = _game->getControlPlayer()->getHandCard();
	m_panel_self->removeAllChildrenWithCleanup(true);
	m_hand_cards.clear();
	for (size_t i = 0; i < cards.size(); ++i)
	{
		auto sprite = CardSprite::create(cards.at(i));
		sprite->setPosition(i * CARD_WIDTH / 2, 0);
		m_panel_self->addChild(sprite);
		m_hand_cards.pushBack(sprite);
	}
	m_panel_self->setContentSize(Size(cards.size() * CARD_WIDTH / 2, CARD_HEIGHT));
}

void GameLayer::updatePlayerCardNum()
{
	auto Text_Card_Num_1 = dynamic_cast<Text *>(getWidgetByName(m_root, "Text_Card_Num_1"));
	auto Text_Card_Num_2 = dynamic_cast<Text *>(getWidgetByName(m_root, "Text_Card_Num_2"));
	Text_Card_Num_1->setString(Value(_game->getPlayer(1)->getHandCardNum()).asString());
	Text_Card_Num_2->setString(Value(_game->getPlayer(2)->getHandCardNum()).asString());
}

void GameLayer::showPlayCardButton(bool is_show)
{
	auto Panel_Button = getWidgetByName(m_root, "Panel_Button");
	Panel_Button->setVisible(is_show);
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	return true;
}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	auto pos = touch->getLocation();
	auto node = event->getCurrentTarget();
	pos = node->convertToNodeSpace(pos);
	CardSprite *card = nullptr;
	for (auto hand_card : m_hand_cards)
	{
		if (hand_card->getBoundingBox().containsPoint(pos))
			card = hand_card;
	}

	if (card != nullptr)
	{
		card->runAction(MoveBy::create(0.2f, Vec2(0, 20)));
	}
}