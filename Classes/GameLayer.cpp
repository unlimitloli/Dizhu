#include "GameLayer.h"
#include "GameMaster.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "CardManager.h"
#include "CardSprite.h"
#include "SceneManager.h"
#include <algorithm>

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace std;

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
	m_panel_out = dynamic_cast<Layout *>(getWidgetByName(m_root, "Panel_Out"));
	m_panel_game = dynamic_cast<Layout *>(getWidgetByName(m_root, "Panel_Game"));

	auto btnExit = dynamic_cast<Button *>(getWidgetByName(m_root, "Button_Exit"));
	btnExit->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::ENDED == type)
		{
			_sceneManager->replaceScene(EnumScene::StartScene);
		}
	});

	auto btnPlay = dynamic_cast<Button *>(getWidgetByName(m_root, "Button_Play"));
	auto btnSkip = dynamic_cast<Button *>(getWidgetByName(m_root, "Button_Skip"));
	auto btnTip = dynamic_cast<Button *>(getWidgetByName(m_root, "Button_Tip"));
	auto btnReset = dynamic_cast<Button *>(getWidgetByName(m_root, "Button_Reset"));
	btnPlay->addTouchEventListener(CC_CALLBACK_2(GameLayer::onTouchButtonPlay, this));
	btnSkip->addTouchEventListener(CC_CALLBACK_2(GameLayer::onTouchButtonSkip, this));
	btnTip->addTouchEventListener(CC_CALLBACK_2(GameLayer::onTouchButtonTip, this));
	btnReset->addTouchEventListener(CC_CALLBACK_2(GameLayer::onTouchButtonReset, this));

	return true;
}

void GameLayer::setReady()
{
	auto Panel_Game = getWidgetByName(m_root, "Panel_Game");
	Panel_Game->setVisible(false);
}

void GameLayer::setStart(Player *player)
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

	m_player = player;
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

	auto Panel_Buyao = getWidgetByName(m_root, "Panel_Buyao");
	Panel_Buyao->setVisible(true);
	clearPlayerPlayCard();

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
		
		if (m_select_cards.contains(card))
		{
			card->runAction(MoveBy::create(0.2f, Vec2(0, -20)));
			m_select_cards.eraseObject(card);
		}
		else
		{
			card->runAction(MoveBy::create(0.2f, Vec2(0, 20)));
			m_select_cards.pushBack(card);
		}
	}
}

void GameLayer::onTouchButtonPlay(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type)
	{
		if (m_select_cards.size() == 0)
			return;
		m_player->playCard(CardType(m_select_cards));
	}
}

void GameLayer::onTouchButtonSkip(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type)
	{
		m_player->playCard(NoneCardType);
	}
}

void GameLayer::onTouchButtonTip(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type)
	{

	}
}

void GameLayer::onTouchButtonReset(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type)
	{

	}
}

void GameLayer::showPlayCard(int player, CardType &card_type)
{
	removePlayerPlayeCard(player);

	if (card_type.isNone())
	{
		auto Image_Buyao = getWidgetByName(m_root, getNameWithIndex("Image_Buyao_%d", player));
		Image_Buyao->setVisible(true);
		return;
	}

	if (player == 0)		// 控制的玩家出牌
	{
		auto select_cards = card_type.getCards();
		int count = select_cards.size();
		for (int i = 0; i < count; ++i)
		{
			auto sprite = CardSprite::create(select_cards.at(i));
			sprite->setPosition(i * CARD_WIDTH / 2, 0);
			m_panel_out->addChild(sprite);
		}
		m_panel_out->setContentSize(Size(m_select_cards.size() * CARD_WIDTH / 2, CARD_HEIGHT));
		m_select_cards.clear();
		flushHandCard();
	}
	else if (player == 1)
	{
		auto Image_PlayerPoint = getWidgetByName(m_root, getNameWithIndex("Image_PlayerPoint_%d", player));
		auto pos = Image_PlayerPoint->getPosition();
		auto other_cards = card_type.getCards();
		auto count = other_cards.size();
		for (int i = 0; i < count; ++i)
		{
			auto sprite = CardSprite::create(other_cards.at(i));
			sprite->setPosition(pos.x + i * CARD_WIDTH / 2, pos.y);
			m_panel_game->addChild(sprite);
			m_card_others[player - 1].pushBack(sprite);
		}
		updatePlayerCardNum();
	}
	else
	{
		auto Image_PlayerPoint = getWidgetByName(m_root, getNameWithIndex("Image_PlayerPoint_%d", player));
		auto pos = Image_PlayerPoint->getPosition();
		auto other_cards = card_type.getCards();
		auto count = other_cards.size();
		for (int i = 0; i < count; ++i)
		{
			auto sprite = CardSprite::create(other_cards.at(i));
			sprite->setPosition(pos.x - (count - i + 1) * CARD_WIDTH / 2, pos.y);
			m_panel_game->addChild(sprite);
			m_card_others[player - 1].pushBack(sprite);
		}
		updatePlayerCardNum();
	}
}

void GameLayer::removePlayerPlayeCard(int player)
{
	if (player == 0)
	{
		m_panel_out->removeAllChildrenWithCleanup(true);
	}
	else
	{
		for (auto sprite : m_card_others[player - 1])
		{
			sprite->removeFromParentAndCleanup(true);
		}
		m_card_others[player - 1].clear();
	}

	auto Image_Buyao = getWidgetByName(m_root, getNameWithIndex("Image_Buyao_%d", player));
	Image_Buyao->setVisible(false);
}

void GameLayer::clearPlayerPlayCard()
{
	for (int i = 0; i < 3; ++i)
	{
		removePlayerPlayeCard(i);
	}
}
