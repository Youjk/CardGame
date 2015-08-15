#include "BattleScene\BattleResultLayer.h"
#include "Utils\AppStringFile.h"


BattleResultLayer::BattleResultLayer(void)
{
	m_coin = 0;
	m_exp = 0;
	m_isTouchEnable = true;
}


BattleResultLayer::~BattleResultLayer(void)
{
}

bool BattleResultLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	InitBk();
	showResult();
	initListener();
	return true;
}

void BattleResultLayer::InitBk()
{
	Size size = Director::getInstance()->getVisibleSize();
	auto bk = Sprite::create("ui/background_1.jpg");
	bk->setPosition(size.width/2, size.height/2);
	bk->setScale(2.23f);
	this->addChild(bk);

	auto titlename_fightcount = Sprite::createWithSpriteFrameName("titlename_fightcount.png");
	titlename_fightcount->setPosition(size.width/2, 700);
	this->addChild(titlename_fightcount);

	auto br_fb = LabelTTF::create(AppStringFile::getInstance()->getStringForKey("battleResult_fb"), "Arial", 35);
	br_fb->setColor(Color3B(255, 255, 0));
	br_fb->setPosition(size.width/2-120, 630);
	this->addChild(br_fb);

	auto br_hero =  LabelTTF::create(AppStringFile::getInstance()->getStringForKey("battleResult_hero"), "Arial", 28);
	br_hero->setColor(Color3B(255, 255, 0));
	br_hero->setPosition(size.width/2+200, 550);
	this->addChild(br_hero);

	auto br_coin =  LabelTTF::create(AppStringFile::getInstance()->getStringForKey("battleResult_getcoin"), "Arial",28);
	br_coin->setPosition(size.width/2-200, 500);
	this->addChild(br_coin);

	br_coin_value = LabelTTF::create("0", "Arial", 28);
	br_coin_value->setAnchorPoint(Vec2(1, 0.5));
	br_coin_value->setPosition(size.width/2+200, 500);
	this->addChild(br_coin_value);

	auto br_exp = LabelTTF::create(AppStringFile::getInstance()->getStringForKey("battleResult_getexp"), "Arial", 28);
	br_exp->setPosition(size.width/2 - 200, 450);
	this->addChild(br_exp);

	br_exp_value = LabelTTF::create("0", "Arial", 28);
	br_exp_value->setAnchorPoint(Vec2(1, 0.5));
	br_exp_value->setPosition(size.width/2 + 200, 450);
	this->addChild( br_exp_value);

	auto br_lv = LabelTTF::create(AppStringFile::getInstance()->getStringForKey("battleResult_lv"), "Arial", 28);
	br_lv->setColor(Color3B(255, 255, 0));
	br_lv->setPosition(Vec2(size.width/2 - 220, 400));
	this->addChild(br_lv);

	//½ø¶ÈÌõ
	auto progress_bk = Sprite::create("ui/exp_0.png");
	progress_bk->setScale(3.0f);
	progress_bk->setPosition(size.width/2 - 180, 400);
	progress_bk->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(progress_bk);

	level_progress = ProgressTimer::create(Sprite::create("ui/exp_1.png"));
	level_progress->setScale(3.0f);
	level_progress->setPercentage(50);
	level_progress->setMidpoint(Vec2(0, 0.5));
	level_progress->setBarChangeRate(Vec2(1, 0));
	level_progress->setType(ProgressTimer::Type::BAR);
	level_progress->setAnchorPoint(Vec2(0, 0.5f));
	level_progress->setPosition(size.width/2-180, 400);
	this->addChild(level_progress);

	auto text_booty = Sprite::createWithSpriteFrameName("text_booty.png");
	text_booty->setPosition(size.width/2, 350);
	this->addChild(text_booty);
}

void BattleResultLayer::showResult()
{
	this->schedule(schedule_selector(BattleResultLayer::changeProgress), 0.01f);
	this->schedule(schedule_selector(BattleResultLayer::changescore), 0.01f);
	this->schedule(schedule_selector(BattleResultLayer::showcard), 0.01f);
}

void BattleResultLayer::changeProgress(float dt)
{
	float level_percentage = level_progress->getPercentage();
	level_percentage += 0.5f;
	
	if (level_percentage > 100)
	{
		this->unschedule(schedule_selector(BattleResultLayer::changeProgress));
	}else
	{
		level_progress->setPercentage(level_percentage);
	}
}

void BattleResultLayer::changescore(float dt)
{
	char p[10] = {0};
	sprintf(p, "%d", m_coin);
	if (m_coin < 888)
	{
		br_coin_value->setString(std::string(p));
		m_coin += 35;
	}

	sprintf(p, "%d", m_exp);
	if (m_exp < 1666)
	{
		br_exp_value->setString(p);
		m_exp += 72;
	}
	
	if(m_coin >= 888 && m_exp >= 1666)
	{
		this->unschedule(schedule_selector(BattleResultLayer::changescore));
	}
}

void BattleResultLayer::showcard(float dt)
{
	auto littlecard_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class2.png");
	littlecard_frame->setPosition(Vec2(100, 250));
	littlecard_frame->setOpacity(0);

	auto littlecard = Sprite::create("ui/littlecard_0480.png");
	littlecard->setPosition(100, 250);
	littlecard->setOpacity(0);
	this->addChild(littlecard);
	this->addChild(littlecard_frame);
	littlecard_frame->runAction(FadeIn::create(1.5f));
	littlecard->runAction(FadeIn::create(1.5f));
}

void BattleResultLayer::initListener()
{
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan  = [this](Touch* touch, Event* event){
		if (m_isTouchEnable)
		{
			return true;
		}else
		{
			return false;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	listener->onTouchEnded =  [this](Touch* touch, Event* event){
		this->removeFromParentAndCleanup(true);
	};
}
