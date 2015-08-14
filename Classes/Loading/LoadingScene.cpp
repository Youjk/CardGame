#include "LoadingScene.h"
#include "Login/LoginScene.h"
#include "CardHero/Hero.h"
#include "Utils/Archives.h"
#include "Utils/AppStringFile.h"

LoadingScene::LoadingScene(void)
{
	_nNumberofLoaded = 0;
}


LoadingScene::~LoadingScene(void)
{
}

Scene* LoadingScene::createScene()
{
	Scene* scene = Scene::create();
	
	auto layer = LoadingScene::create();
	scene->addChild(layer);

	return scene;
}

bool LoadingScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	initUI();   //加载布局
	LoadPicResourceToCache();  //异步加载资源
	LoadHeroProperty();   //加载英雄的属性值
	AppStringFile::getInstance();

	auto backlistener = EventListenerKeyboard::create();
	backlistener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){
		switch(keyCode)
		{        
			//监听返回键        
			case EventKeyboard::KeyCode::KEY_ESCAPE:              
				Director::getInstance()->end();            
				break;        
			//监听menu键        
			case EventKeyboard::KeyCode::KEY_MENU:             
				break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backlistener, this);

	return true;
}


void LoadingScene::initUI()
{
	Size visibleSize = Director::getInstance()->getWinSize();

	//加载logo图标
	auto logo = Sprite::create("ui/logo.png");
	logo->setPosition(visibleSize.width / 2, visibleSize.height /2);
	this->addChild(logo);

	//加载游戏名
	auto gameNameLabel = Label::createWithBMFont("fonts/ziti_2.fnt", "Card Game");
	gameNameLabel->setPosition(Point(visibleSize.width/2 ,visibleSize.height));
	gameNameLabel->setColor(Color3B(255, 255 , 0));
	gameNameLabel->setScale(1.5f);
	this->addChild(gameNameLabel);
	gameNameLabel->runAction(EaseElasticOut::create(MoveTo::create(1.5f, Vec2(visibleSize.width/2, visibleSize.height  - gameNameLabel->getContentSize().height - 200.0f))));

	// loading边框
	auto progressFrame = Sprite::create("ui/loadingbarbd.png");
	this->addChild(progressFrame);
	progressFrame->setPosition(visibleSize.width / 2, visibleSize.height /2);

	//loadingBar
	_loadProgress = ProgressTimer::create(Sprite::create("ui/loadingbar.png"));
	_loadProgress->setType(ProgressTimer::Type::BAR);
	_loadProgress->setBarChangeRate(Vec2(1, 0)); //设置进度条变化方向
	_loadProgress->setMidpoint(Point(0, 1));//设置进度的起点
	_loadProgress->setPosition(visibleSize.width / 2, visibleSize.height / 2 );
	_loadProgress->setPercentage(0);
	this->addChild(_loadProgress);

	//加载loading。。。文字
	auto ladingLabel = Label::createWithBMFont("fonts/ziti_2.fnt", "Loading...");
	ladingLabel->setPosition(Point(visibleSize.width/2 ,visibleSize.height/2 + ladingLabel->getContentSize().height));
	ladingLabel->setColor(Color3B(255, 255 , 0));
	this->addChild(ladingLabel);

	//加载author
	auto authorLabel = Label::createWithBMFont("fonts/ziti_2.fnt", "copyright : xmu_yjk");
	authorLabel->setPosition(Point(visibleSize.width/2 ,authorLabel->getContentSize().height));
	authorLabel->setColor(Color3B(255, 255 , 0));
	this->addChild(authorLabel);
}

//异步加载资源
void LoadingScene::LoadPicResourceToCache()
{
	auto textureCache = Director::getInstance()->getTextureCache();

	textureCache->addImageAsync("ui/bigcard_0000_0004.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/bigcard_0329_0335.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/bigcard_0337_0343.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/bigcard_0345_0351.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));

	textureCache->addImageAsync("ui/bigcard_0489_0494.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/bigcard_frame_greenandblue.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/bigcard_frame_purpleandyellow.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/bigcard_frame_white.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));

	textureCache->addImageAsync("ui/eatcard_part1.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/equipment_part1.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/equipment_part2.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/evolution.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));

	textureCache->addImageAsync("ui/fight_star.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/fight_victroy.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/heal.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/login_animation.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));

	textureCache->addImageAsync("ui/play_image.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/play_script1.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/play_script2.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/skill_customattack.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));

	textureCache->addImageAsync("ui/raffle.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/skill_tenarmy.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/skill_thunde.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/skill_windhit.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));

	textureCache->addImageAsync("ui/skill_zhongji.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/skille_blizzard.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_arena.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_eatcard.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));

	textureCache->addImageAsync("ui/ui_fight.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_friend.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_icon.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_list_button.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));

	textureCache->addImageAsync("ui/ui_listbutton1.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_littcard_frame.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_littlebutton.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_mainface.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));

	textureCache->addImageAsync("ui/ui_navigation.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_occupation.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_rank.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_serverlist.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
	textureCache->addImageAsync("ui/ui_text.png", CC_CALLBACK_1(LoadingScene::LoadPicResourceCallBack,this));
}

//异步加载资源回调函数
void LoadingScene::LoadPicResourceCallBack(Texture2D *textture)
{
	auto frameCache = SpriteFrameCache::getInstance();
	switch (_nNumberofLoaded++)
	{
	case 0:
		frameCache->addSpriteFramesWithFile("ui/bigcard_0000_0004.plist", textture);
		break;
	case 1:
		frameCache->addSpriteFramesWithFile("ui/bigcard_0329_0335.plist", textture);
		break;
	case 2:
		frameCache->addSpriteFramesWithFile("ui/bigcard_0337_0343.plist", textture);
		break;
	case 3:
		frameCache->addSpriteFramesWithFile("ui/bigcard_0345_0351.plist", textture);
		break;
	case 4:
		frameCache->addSpriteFramesWithFile("ui/bigcard_0489_0494.plist", textture);
		break;
	case 5:
		frameCache->addSpriteFramesWithFile("ui/bigcard_frame_greenandblue.plist", textture);
		break;
	case 6:
		frameCache->addSpriteFramesWithFile("ui/bigcard_frame_purpleandyellow.plist", textture);
		break;
	case 7:
		frameCache->addSpriteFramesWithFile("ui/bigcard_frame_white.plist", textture);
		break;
	case 8:
		frameCache->addSpriteFramesWithFile("ui/eatcard_part1.plist", textture);
		break;
	case 9:
		frameCache->addSpriteFramesWithFile("ui/equipment_part1.plist", textture);
		break;
	case 10:
		frameCache->addSpriteFramesWithFile("ui/equipment_part2.plist", textture);
		break;
	case 11:
		frameCache->addSpriteFramesWithFile("ui/evolution.plist", textture);
		break;
	case 12:
		frameCache->addSpriteFramesWithFile("ui/fight_star.plist", textture);
		break;
	case 13:
		frameCache->addSpriteFramesWithFile("ui/fight_victroy.plist", textture);
		break;
	case 14:
		frameCache->addSpriteFramesWithFile("ui/heal.plist", textture);
		break;
	case 15:
		frameCache->addSpriteFramesWithFile("ui/login_animation.plist", textture);
		break;
	case 16:
		frameCache->addSpriteFramesWithFile("ui/play_image.plist", textture);
		break;
	case 17:
		frameCache->addSpriteFramesWithFile("ui/play_script1.plist", textture);
		break;
	case 18:
		frameCache->addSpriteFramesWithFile("ui/play_script2.plist", textture);
		break;
	case 19:
		frameCache->addSpriteFramesWithFile("ui/skill_customattack.plist", textture);
		break;
	case 20:
		frameCache->addSpriteFramesWithFile("ui/raffle.plist", textture);
		break;
	case 21:
		frameCache->addSpriteFramesWithFile("ui/skill_tenarmy.plist", textture);
		break;
	case 22:
		frameCache->addSpriteFramesWithFile("ui/skill_thunde.plist", textture);
		break;
	case 23:
		frameCache->addSpriteFramesWithFile("ui/skill_windhit.plist", textture);
		break;
	case 24:
		frameCache->addSpriteFramesWithFile("ui/skill_zhongji.plist", textture);
		break;
	case 25:
		frameCache->addSpriteFramesWithFile("ui/skille_blizzard.plist", textture);
		break;
	case 26:
		frameCache->addSpriteFramesWithFile("ui/ui_arena.plist", textture);
		break;
	case 27:
		frameCache->addSpriteFramesWithFile("ui/ui_eatcard.plist", textture);
		break;
	case 28:
		frameCache->addSpriteFramesWithFile("ui/ui_fight.plist");
		break;
	case 29:
		frameCache->addSpriteFramesWithFile("ui/ui_friend.plist");
		break;
	case 30:
		frameCache->addSpriteFramesWithFile("ui/ui_icon.plist");
		break;
	case 31:
		frameCache->addSpriteFramesWithFile("ui/ui_list_button.plist");
		break;
	case 32:
		frameCache->addSpriteFramesWithFile("ui/ui_listbutton1.plist");
		break;
	case 33:
		frameCache->addSpriteFramesWithFile("ui/ui_littcard_frame.plist");
		break;
	case 34:
		frameCache->addSpriteFramesWithFile("ui/ui_littlebutton.plist");
		break;
	case 35:
		frameCache->addSpriteFramesWithFile("ui/ui_mainface.plist");
		break;
	case 36:
		frameCache->addSpriteFramesWithFile("ui/ui_navigation.plist");
		break;
	case 37:
		frameCache->addSpriteFramesWithFile("ui/ui_occupation.plist");
		break;
	case 38:
		frameCache->addSpriteFramesWithFile("ui/ui_rank.plist");
		break;
	case 39:
		frameCache->addSpriteFramesWithFile("ui/ui_serverlist.plist");
		break;
	case 40:
		frameCache->addSpriteFramesWithFile("ui/ui_text.plist");
		this->scheduleOnce(schedule_selector(LoadingScene::gotoNextScene), 0.2f);
		break;
	default:
		break;
	}

	_loadProgress->setPercentage(_nNumberofLoaded * 100.0 / TOTALNUMPICTURE);
}

//跳转到下一个场景
void LoadingScene::gotoNextScene(float dt)
{
	Director::getInstance()->replaceScene(LoginScene::createScene());
}

//加载英雄属性
void LoadingScene::LoadHeroProperty()
{
	//log(FileUtils::getInstance()->getWritablePath().c_str());
	Hero* hero = Hero::getInstance();
	if (Archives::getInstance()->isExist())
	{
		//若已经玩过，则读取当前玩过的属性
		Archives::getInstance()->getHero_Property(*hero);
	}
	else
	{
		//否则设置初始值
		 hero->setName("kun");
		 hero->setLevel(1);
		 hero->setDiamond(100);
		 hero->setExp(100);
		 hero->setStrength(100);
		 hero->setMoney(100);
		 hero->setLeaderShip(0);
		 hero->setTeamLv(100);
		 hero->setRank(1);
		UserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);
		Archives::getInstance()->setHero_Property(*hero);
	}
}

