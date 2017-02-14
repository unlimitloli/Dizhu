#include "GameLayer.h"
#include "GameMaster.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "CardManager.h"
#include "CardSprite.h"

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
