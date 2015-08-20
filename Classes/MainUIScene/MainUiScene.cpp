#include "MainUiScene.h"
#include "CardHero/Hero.h"
#include "Utils/AppStringFile.h"
#include "Utils/ValueConvert.h"
#include "Utils/TimeUtils.h"
#include "MainUIScene/MainTopTouchLayer.h"
#include "Dialog/DialogLayer.h"
#include "BattleScene/BattleResultLayer.h"




MainUiScene::MainUiScene(void)
{
	_mutiplexLayer = NULL;
}


MainUiScene::~MainUiScene(void)
{

}

Scene* MainUiScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainUiScene::create();
	scene->addChild(layer);
	
	return scene;
}

bool MainUiScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	ConfigureMultiplexLayer();
	ConfigureTopUI();     //初始化顶部UI
	ConfigureButtonUI();  //初始化底部MenuUI
	ScrollText();
	ConfigureTouchLayer();   //加入顶部触摸层
	
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MainUiScene::show_BattleResult), "showBattleResult", NULL);

	auto backlistener = EventListenerKeyboard::create();
	backlistener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){
		switch(keyCode)
		{        
			//监听返回键        
		case EventKeyboard::KeyCode::KEY_ESCAPE:              
			Director::getInstance()->popScene();            
			break;        
			//监听menu键        
		case EventKeyboard::KeyCode::KEY_MENU:             
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backlistener, this);

	return true;
}

//顶部点击弹出触摸层
void MainUiScene::ConfigureTouchLayer()
{
	auto mainTouchLayer = MainTopTouchLayer::create();
	this->addChild(mainTouchLayer);
}


//底部tab切换
void MainUiScene::ConfigureMultiplexLayer()
{
	_mainUILayer = MainUILayer::create();
	_instanceUILayer = InstanceLayer::create();
	_fightLayer = FightLayer::create();
	_storeLayer = StoreLayer::create();
	_socialLayer = SocialLayer::create();
	_moreLayer = MoreLayer::create();

	_mutiplexLayer = LayerMultiplex::create(_mainUILayer, _instanceUILayer, _fightLayer, _storeLayer, _socialLayer, _moreLayer, NULL);
	this->addChild(_mutiplexLayer);
}

//顶部状态UI
void MainUiScene::ConfigureTopUI()
{
	Size size = Director::getInstance()->getVisibleSize();

	//顶部状态
	auto top = Sprite::createWithSpriteFrameName("top.png");
	top->setAnchorPoint(Vec2(0.5f, 1.0f));
	top->setPosition(size.width/2, size.height);
	this->addChild(top, 5);
	top->setTag(MAIN_TOP);

	//军衔
	auto icon_rank = Sprite::createWithSpriteFrameName("rank_15.png");
	icon_rank->setPosition(35, top->getContentSize().height - 27);
	top->addChild(icon_rank);

	//名字
	auto playerName = LabelTTF::create(AppStringFile::getInstance()->getStringForKey("playername").c_str(), "Arial", 25);
	playerName->setPosition(130, top->getContentSize().height - 27);
	playerName->setColor(Color3B(255, 255, 0));
	top->addChild(playerName);

	//等级
	auto text_lv = Sprite::createWithSpriteFrameName("info_lv.png");
	text_lv->setPosition(338, top->getContentSize().height - 38);
	top->addChild(text_lv);
	auto lv = Label::createWithBMFont("fonts/ziti_2.fnt", "Lv." + ValueConvert::intTostring(Hero::getInstance()->getLevel()));
	lv->setScale(0.6f);
		//WithTTF("Lv." + ValueConvert::intTostring(Hero::getInstance()->getLevel()), "fonts/Arial.ttf", 25);
	lv->setColor(Color3B(255, 255, 0));
	lv->setPosition(400, top->getContentSize().height - 38);
	top->addChild(lv);
	
	//符石
	auto diamond = LabelTTF::create(ValueConvert::intTostring(Hero::getInstance()->getDiamond()), "Arial", 25);
	diamond->setColor(Color3B(0, 255, 0));
	diamond->setAnchorPoint(Vec2(1.0, 0.5));
	diamond->setPosition(620, top->getContentSize().height - 50);
	top->addChild(diamond);

	//金币
	auto money = LabelTTF::create(ValueConvert::intTostring(Hero::getInstance()->getMoney()), "Arial", 25);
	money->setColor(Color3B(255, 255, 0));
	money->setAnchorPoint(Vec2(1.0, 0.5));
	money->setPosition(620, top->getContentSize().height - 110);
	top->addChild(money);

	//经验条
	auto info_exp = Sprite::createWithSpriteFrameName("info_exp.png");
	info_exp->setPosition(52, 113);
	top->addChild(info_exp);
	auto expbg = Sprite::create("ui/exp_0.png");
	expbg->setScale(2.8f);
	expbg->setPosition(260, 113);
	top->addChild(expbg);
	auto exp = ProgressTimer::create(Sprite::create("ui/exp_1.png"));
	exp->setScale(2.8f);
	exp->setPosition(260, 115);
	exp->setBarChangeRate(Vec2(1, 0));
	exp->setMidpoint(Vec2(0, 1));
	exp->setType(ProgressTimer::Type::BAR);
	//exp->setReverseDirection(true);

	
	float expPerencetage = 50.0f;
	exp->setPercentage(expPerencetage);
	top->addChild(exp);
	
	//体力槽
	auto info_strength = Sprite::createWithSpriteFrameName("info_strength.png");
	info_strength->setPosition(50, 68);
	top->addChild(info_strength);
	auto strengthbg = Sprite::create("ui/strength_0.png");
	strengthbg->setScale(2.3f);
	strengthbg->setPosition(230, 60);
	top->addChild(strengthbg);
	auto strength = ProgressTimer::create(Sprite::create("ui/strength_1.png"));
	//设置进度条长度和宽度开始变化的大小,进度条横向移动
	strength->setBarChangeRate(Vec2(1,0));
	//设置进度条为水平
	strength->setType(ProgressTimer::Type::BAR);
	strength->setScale(2.3f);
	strength->setPosition(230, 60);
	strength->setMidpoint(Vec2(0, 1));
	strength->setPercentage(50.0f);

	top->addChild(strength);
	strength->setTag(MAIN_TOP_STRENGTH_PROGRESS);

	//time和 体力值
	auto text_time = LabelTTF::create(AppStringFile::getInstance()->getStringForKey("timetext"), "Arial", 25);
	text_time->setPosition(120, 77);
	top->addChild(text_time);
	auto time = LabelTTF::create(TimeUtils::getSystemTime(), "Arial", 25);
	time->setPosition(210, 77);
	top->addChild(time);
	time->setTag(MAIN_TOP_STRENGTH_TIME);
	
	pStrTemp.initWithFormat("%d/100", Hero::getInstance()->getStrength());
	auto strength_value = LabelTTF::create(pStrTemp.getCString(), "Arial", 25);
	strength_value->setPosition(320, 77);
	top->addChild(strength_value);
	strength_value->setTag(MAIN_TOP_STRENGTH_VALUE);

	this->schedule(schedule_selector(MainUiScene::updatestrengthtime), 1.0);
}

//初始化顶部底部的按钮UI
void MainUiScene::ConfigureButtonUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//主页按钮
	auto button_homePage_normal = Sprite::createWithSpriteFrameName("button_homepage_0.png");
	auto button_homePage_select = Sprite::createWithSpriteFrameName("button_homepage_1.png");
	auto button_homePage_Disable = Sprite::createWithSpriteFrameName("button_homepage_2.png");
	auto button_homepage_item = MenuItemSprite::create(button_homePage_normal, button_homePage_select, button_homePage_Disable, CC_CALLBACK_1(MainUiScene::button_Homepage, this));

	//副本按钮
	auto button_instance_normal = Sprite::createWithSpriteFrameName("button_instance_0.png");
	auto button_instance_select = Sprite::createWithSpriteFrameName("button_instance_1.png");
	auto button_instance_Disable = Sprite::createWithSpriteFrameName("button_instance_2.png");
	auto button_instance_item = MenuItemSprite::create(button_instance_normal, button_instance_select, button_instance_Disable, CC_CALLBACK_1(MainUiScene::button_Instance, this));

	//战斗按钮
	auto button_fight_normal = Sprite::createWithSpriteFrameName("button_fight_0.png");
	auto button_fight_select = Sprite::createWithSpriteFrameName("button_fight_1.png");
	auto button_fight_Disable = Sprite::createWithSpriteFrameName("button_fight_2.png");
	auto button_fight_item = MenuItemSprite::create(button_fight_normal, button_fight_select, button_fight_Disable, CC_CALLBACK_1(MainUiScene::button_Fight, this));

	//商店按钮
	auto button_store_normal = Sprite::createWithSpriteFrameName("button_store_0.png");
	auto button_store_select = Sprite::createWithSpriteFrameName("button_store_1.png");
	auto button_store_Disable = Sprite::createWithSpriteFrameName("button_store_2.png");
	auto button_store_item = MenuItemSprite::create(button_store_normal, button_store_select, button_store_Disable, CC_CALLBACK_1(MainUiScene::button_Store, this));

	//好友按钮
	auto button_social_normal = Sprite::createWithSpriteFrameName("button_social_0.png");
	auto button_social_select = Sprite::createWithSpriteFrameName("button_social_1.png");
	auto button_social_Disable = Sprite::createWithSpriteFrameName("button_social_2.png");
	auto button_social_item = MenuItemSprite::create(button_social_normal, button_social_select, button_social_Disable, CC_CALLBACK_1(MainUiScene::button_Social, this));

	//攻略按钮
	auto button_more_normal = Sprite::createWithSpriteFrameName("button_more_0.png");
	auto button_more_select = Sprite::createWithSpriteFrameName("button_more_1.png");
	auto button_more_Disable = Sprite::createWithSpriteFrameName("button_more_2.png");
	auto button_more_item = MenuItemSprite::create(button_more_normal, button_more_select, button_more_Disable, CC_CALLBACK_1(MainUiScene::button_More, this));

	//添加底部菜单
	auto mainMenu = Menu::create(button_homepage_item, button_instance_item, button_fight_item, button_store_item, button_social_item, button_more_item, NULL);
	mainMenu->alignItemsHorizontallyWithPadding(-19);
	mainMenu->setPosition(visibleSize.width/2 , button_homePage_normal->getContentSize().height/2);
	this->addChild(mainMenu);
}

void MainUiScene::ScrollText()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	text = LabelTTF::create(AppStringFile::getInstance()->getStringForKey("Game_Gonggao"), "Arial", 28);
	text->setPosition(visibleSize.width + text->getContentSize().width / 2, 125);
	text->setColor(Color3B(255,255, 0));
	this->addChild(text, 3);
	this->scheduleUpdate();
}

void MainUiScene::show_BattleResult(Ref* pSender)
{
	_battleResultLayer = BattleResultLayer::create();
	this->addChild(_battleResultLayer, 4);
}

void MainUiScene::update(float dt)
{
	//滚动字幕
	Size visivleSize = Director::getInstance()->getVisibleSize();

	int newX = text->getPositionX() - 1;
	if (newX <= -text->getContentSize().width/2)
	{
		newX = visivleSize.width + text->getContentSize().width/2;
	}
	text->setPositionX(newX);
}

//更新时间label
void MainUiScene::updatestrengthtime(float dt)
{
	//每隔1s更新时间
	((LabelTTF*)(this->getChildByTag(MAIN_TOP)->getChildByTag(MAIN_TOP_STRENGTH_TIME)))->setString(TimeUtils::getSystemTime());
}

std::string  MainUiScene::getstrengthTime(std::string strcurtime)
{
	std::string strmin(strcurtime, 0 , 2);
	int min = atoi(strmin.c_str());
	std::string strsec(strcurtime, 3.2);
	int sec = atoi(strsec.c_str());
	//log(strmin.c_str());
	//log(strsec.c_str());

	return "";
}

std::string  MainUiScene::getstrengthValue(std::string strcurvalue)
{
	return "";
}

//主页按钮回调
void MainUiScene::button_Homepage(Ref* pSender)
{
	_mainUILayer->restoreToMainUI();
	_mutiplexLayer->switchTo(0);
}

//副本按钮回调
void MainUiScene::button_Instance(Ref* pSender)
{
	_mutiplexLayer->switchTo(1);
	_instanceUILayer->call_by_main();
}

void MainUiScene::button_Fight(Ref* pSender)
{
	_mutiplexLayer->switchTo(2);
}

void MainUiScene::button_Store(Ref* pSender)
{
	_mutiplexLayer->switchTo(3);
}

void MainUiScene::button_Social(Ref* pSender)
{
	_mutiplexLayer->switchTo(4);
}

void MainUiScene::button_More(Ref* pSender)
{
	_mutiplexLayer->switchTo(5);
}
