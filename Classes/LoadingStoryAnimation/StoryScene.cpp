#include "StoryScene.h"
#include "MainUIScene/MainUiScene.h"

USING_NS_CC;
StoryScene::StoryScene(void)
{
	story_scene_xing = NULL;
	backgroud1 = NULL;
}


StoryScene::~StoryScene(void)
{
}

Scene* StoryScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StoryScene::create();

	scene->addChild(layer);
	return scene;
}

bool StoryScene::init()
{
	if (!Layer::create())
	{
		return false;
	}

	//¼ÌÐøÓÎÏ·°´Å¥
	auto menuSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_textbase.png"));
	auto menu_passStory = MenuItemSprite::create(menuSprite, menuSprite, menuSprite, CC_CALLBACK_1(StoryScene::pass_story, this));
	menu_passStory->setScale(2.0);
	menu_passStory->setPosition(Point::ZERO);
	auto menu = Menu::create(menu_passStory, NULL);
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(680, 900);
	this->addChild(menu, 3);

	//¼ÌÐøÓÎÏ·ÎÄ×Ö
	auto text_passStory = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("button_next.png"));
	text_passStory->setPosition(550, 900);
	this->addChild(text_passStory, 4);

	//¿ªÊ¼³¡¾°1
	begin_scene1();

	auto backlistener = EventListenerKeyboard::create();
	backlistener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){
		switch(keyCode)
		{        
			//¼àÌý·µ»Ø¼ü        
		case EventKeyboard::KeyCode::KEY_ESCAPE:              
			Director::getInstance()->popScene();            
			break;        
			//¼àÌýmenu¼ü        
		case EventKeyboard::KeyCode::KEY_MENU:             
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backlistener, this);

	return true;
}

void StoryScene::pass_story(Ref* pSedenr)
{
	//Ìø×ª³¡¾°
	this->unscheduleAllCallbacks();
	Director::getInstance()->replaceScene(MainUiScene::createScene());
}

void StoryScene::begin_scene1()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//±³¾°1£¬ÐÇÐÇÉ³Ä®±³¾°£¬Ö´ÐÐËõ·ÅºÍµ­Èë¶¯»­
	backgroud1 = Sprite::createWithSpriteFrameName("play_01tu1.jpg");
	backgroud1->setScale(2.0f);
	backgroud1->setOpacity(0);
	auto backgroundScale = ScaleBy::create(1.0f, 0.8f);
	auto backgroundFadeIn = FadeIn::create(5.0f);
	auto backgroundSpwan = Spawn::create(backgroundScale, backgroundFadeIn, NULL);
	backgroud1->runAction(backgroundSpwan);
	backgroud1->setAnchorPoint(Vec2(0, 1));
	backgroud1->setPosition(0, visibleSize.height);
	this->addChild(backgroud1);

	//×ÖÄ¸ºÚÉ«±³¾°
	auto play_heibel = Sprite::createWithSpriteFrameName("play_heibei.png");
	play_heibel->setScaleY(2.0f);
	play_heibel->setScaleX(8.0f);
	play_heibel->setAnchorPoint(Point::ZERO);
	play_heibel->setPosition(Point::ZERO);
	this->addChild(play_heibel);

	//×ÖÄ»ÏÔÊ¾£¬ÀûÓÃlambda±í´ïÊ½
	this->scheduleOnce([&](float dt){
		showText("play_1tuzi1.png");
			}, 2.0f, "1");
	this->scheduleOnce([&](float dt){
		showText("play_1tuzi2.png");
	}, 4.5f, "2");

	//ÐÇÐÇÉÁË¸
	auto xing_Delay = DelayTime::create(3.0f);
	auto xing_Func = CallFunc::create(CC_CALLBACK_0(StoryScene::xingFlash, this));
	auto xing_seq = Sequence::create(xing_Delay, xing_Func, NULL);
	this->runAction(xing_seq);


	//ÇÐ»»µ½³¡¾°2
	this->scheduleOnce(schedule_selector(StoryScene::end_scene1), 8.0f);
	this->scheduleUpdate();
}

void StoryScene::update(float delta)
{

	backgroud1->setPositionX(backgroud1->getPositionX() - 0.1);


	if (story_scene_xing != NULL)
	{
		story_scene_xing->setPositionX(story_scene_xing->getPositionX() - 0.1);
	}
}



void StoryScene::end_scene1(float dt)
{
	//µÚÒ»²½±³¾°µ­³ö
	auto backgroud1_fadeOut = FadeOut::create(1.0f);
	backgroud1->runAction(backgroud1_fadeOut);
	auto xing_fadeout = FadeOut::create(1.0f);
	story_scene_xing->runAction(xing_fadeout);

	//¿ªÆôµÚ¶þÄ»
	auto delaytime = DelayTime::create(1.0f);
	auto begin_scene2_func = CallFunc::create(CC_CALLBACK_0(StoryScene::begin_scene2,this));
	this->runAction(Sequence::create(delaytime, begin_scene2_func, NULL));
}

//ÐÇÐÇÉÁË¸¶¯»­
void StoryScene::xingFlash()
{
	story_scene_xing = Sprite::createWithSpriteFrameName("play_xing.png");
	story_scene_xing->setPosition(384, 742);
	this->addChild(story_scene_xing);
	
	auto xing_fadeIn1 = FadeIn::create(0.8f);
	auto xing_fadeOut1 = FadeOut::create(0.8f);
	auto xing_sequence = Sequence::create(xing_fadeIn1, xing_fadeOut1,xing_fadeIn1,NULL);
	auto xing_repeat = Repeat::create(xing_sequence, 2);

	story_scene_xing->runAction(xing_repeat);
}

void StoryScene::showText(const char* pszName, float delaytime, Point initposition, Point moveposition, bool isDisapper)
{
	//×ÖÄ»ÏÔÊ¾
	auto sprite = Sprite::createWithSpriteFrameName(pszName);
	sprite->setAnchorPoint(Vec2(0, 1));
	sprite->setPosition(initposition);
	sprite->setScale(1.2f);
	this->addChild(sprite, 2);

	//×ÖÄ»¶¯»­
	auto srite_moveby = MoveBy::create(1.0f, moveposition);
	if (isDisapper)
	{
		//×ÖÄ»1Í£Áô
		auto sprite_delay = DelayTime::create(delaytime);
		//×ÖÄ»½¥Òþ
		auto sprite_fadeout = FadeOut::create(1.0f);
		//×ÖÄ»ÒÆ³ý
		auto sprite_remove = CallFunc::create([&]{
			this->removeChild(sprite);
		});

		auto sequence = Sequence::create(srite_moveby, sprite_delay, sprite_fadeout, sprite_remove, NULL);
		sprite->runAction(sequence);
	}else
	{
		sprite->runAction(srite_moveby);
	}
}

void StoryScene::begin_scene2()
{
	Size size = Director::getInstance()->getVisibleSize();

	//¹Ø±ÕËùÓÐ¼ÆÊ±Æ÷£¬ÒÆ³ý±³¾°1ºÍÐÇÐÇ
	this->unscheduleAllCallbacks();
	this->removeChild(backgroud1,true);
	this->removeChild(story_scene_xing, true);

	//¼ÓÈë±³¾°Í¼Æ¬2
	backgroud2 = Sprite::createWithSpriteFrameName("play_02tu2.jpg");
	backgroud2->setScale(1.8f);
	backgroud2->setAnchorPoint(Vec2(0.5, 1));
	backgroud2->setPosition(size.width/2, size.height + 120);
	this->addChild(backgroud2);

	//Ìí¼Ó»ð¶Ñ
	huodui = Sprite::createWithSpriteFrameName("play_huodui.png");
	huodui->setPosition(120, 380);
	this->addChild(huodui);

	//Ìí¼ÓMT
	play_mt = Sprite::createWithSpriteFrameName("play_mtt.png");
	play_mt->setAnchorPoint(Vec2(0.5, 0.5));
	play_mt->setPosition(415, 325);
	this->addChild(play_mt);

	//Ìí¼Ódede
	play_dede = Sprite::createWithSpriteFrameName("play_dede.png");
	play_dede->setAnchorPoint(Vec2(0.5, 0.5));
	play_dede->setPosition(310, 325);
	this->addChild(play_dede);

	//Ìí¼ÓÉµÂù
	play_shaman= Sprite::createWithSpriteFrameName("play_shaman.png");
	play_shaman->setAnchorPoint(Vec2(0.5, 0.5));
	play_shaman->setPosition(205, 325);
	this->addChild(play_shaman);

	//×ÖÄ»ÏÔÊ¾£¬ÀûÓÃlambda±í´ïÊ½
	this->scheduleOnce([&](float dt){
		showText("play_2zi1z.png");
		shakeHead(play_shaman);
		showTextBox("play_shakuang01.png", Point(245, 360));
	}, 1.0f, "1");

	this->scheduleOnce([&](float dt){
		showText("play_2zi2z.png");
		shakeHead(play_mt);
		showTextBox("play_mtkuang01.png", Point(380, 380));
	}, 3.5f, "2");

	this->scheduleOnce([&](float dt){
		showText("play_2zi3z.png");
		shakeHead(play_shaman);
		showTextBox("play_shakuang02.png", Point(245, 360));
	}, 6.0f, "3");

	this->scheduleOnce([&](float dt){
		showText("play_2zi4z.png");
		shakeHead(play_mt);
		showTextBox("play_mtkuang02.png", Point(380, 380));
	}, 8.5f, "4");

	this->scheduleOnce([&](float dt){
		showText("play_2zi5z.png");
		shakeHead(play_dede);
		showTextBox("play_dekuang01.png", Point(270, 380));
	}, 11.0f, "5");

	this->scheduleOnce(schedule_selector(StoryScene::end_sence2), 14.0f);
}

void StoryScene::end_sence2(float dt)
{
	auto fadeout = FadeOut::create(1.0f);

	//µÚÒ»²½±³¾°µ­³ö
	backgroud2->runAction((FadeOut*)fadeout->clone());
	huodui->runAction((FadeOut*)fadeout->clone());

	//Ö÷½Ç¼ä½¥ÒþÉí
	play_mt->runAction((FadeOut*)fadeout->clone());
	play_shaman->runAction((FadeOut*)fadeout->clone());
	play_dede->runAction((FadeOut*)fadeout->clone());

	//¿ªÆôµÚ3Ä»
	auto delaytime = DelayTime::create(1.0f);
	auto begin_scene3_func = CallFunc::create(CC_CALLBACK_0(StoryScene::begin_scene3,this));
	this->runAction(Sequence::create(delaytime, begin_scene3_func, NULL));
}

//Ðý×ª¶¯»­
void StoryScene::shakeHead(Sprite*& sprite)
{
	auto rotate1 = RotateTo::create(0.5f, 5.0f, 0);
	auto rotate2 = RotateTo::create(0.5f, -5.0f, 0);
	auto rotate3 = RotateTo::create(0.5f, 0, 0);

	auto sequence = Sequence::create(rotate1, rotate2, rotate3, NULL);

	sprite->runAction(sequence);
}

//ÏÔÊ¾¶Ô»°
void StoryScene::showTextBox(const char* pszName, Point position)
{
	//Ìí¼Ósprite
	auto sprite = Sprite::createWithSpriteFrameName(pszName);
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(position);
	sprite->setScale(0.5f);
	this->addChild(sprite);

	//scale¶¯»­
	auto scale = ScaleTo::create(1.0f, 1.0f);
	auto delay = DelayTime::create(1.5f);
	auto fadeout = FadeOut::create(1.0f);
	auto sprite_remove = CallFunc::create([&]{
		this->removeChild(sprite);
	});

	sprite->runAction(Sequence::create(scale, delay, fadeout, NULL));
}

void StoryScene::begin_scene3()
{
	Size size = Director::getInstance()->getVisibleSize();

	//¹Ø±ÕËùÓÐ¼ÆÊ±Æ÷£¬ÒÆ³ý±³¾°1ºÍÐÇÐÇ
	this->unscheduleAllCallbacks();
	this->removeChild(backgroud2,true);
	this->removeChild(huodui, true);
	this->removeChild(play_mt);
	this->removeChild(play_shaman);
	this->removeChild(play_dede);

	//Ìí¼Ó±³¾°3
	background3 = Sprite::createWithSpriteFrameName("play_03tu1.jpg");
	background3->setScale(1.8f);
	background3->setAnchorPoint(Vec2(0.5, 1));
	background3->setPosition(size.width/2, size.height + 120);
	background3->setOpacity(0);
	FadeIn* fadeIn = FadeIn::create(0.3f);
	background3->runAction(fadeIn);
	this->addChild(background3);

	this->scheduleOnce([&](float dt){
		showLines();
	}, 0.5f, "1");

	this->scheduleOnce([&](float dt){
		showText("play_03zi1.png");
	}, 1.0f, "2");

	this->scheduleOnce([&](float dt){
		showBoom_1();
	}, 1.5f, "3");

	this->scheduleOnce([&](float dt){
		showText("play_03zi2.png");
	}, 3.5f, "4");

	this->scheduleOnce(schedule_selector(StoryScene::end_sence3), 5.5f);
}

void StoryScene::end_sence3(float dt)
{
	this->removeAllChildren();
	Director::getInstance()->replaceScene(MainUiScene::createScene());
	//³¡¾°Ìø×ª
}

void StoryScene::showLines()
{
	Size size = Director::getInstance()->getVisibleSize();

	auto guangxian = Sprite::createWithSpriteFrameName("play_guangxian.png");
	guangxian->setAnchorPoint(Vec2(0.5, 0.5));
	guangxian->setScale(3.2f);
	guangxian->setPosition(size.width/2, size.height/2 + 90);
	this->addChild(guangxian);

	//ÉÁË¸£¬½¥Òþ
	auto blink = Blink::create(0.5f, 3);
	auto delaytime = DelayTime::create(1.5f);
	auto fadeOut = FadeOut::create(0.5f);
	auto guangxian_remove = CallFunc::create([&]{
		this->removeChild(guangxian);
	});
	guangxian->runAction(blink);
	guangxian->runAction(Sequence::create(delaytime, fadeOut, guangxian_remove, NULL));
}

void StoryScene::showBoom_1()
{
	boom1_1 = Sprite::createWithSpriteFrameName("play_bao2.png");
	boom1_1->setPosition(750, 690);
	this->addChild(boom1_1, 2);

	auto moveBy = MoveBy::create(0.1f, Vec2(-200, -200));
	auto boomDone = CallFunc::create([&]{
		boom1_2 = Sprite::createWithSpriteFrameName("play_bao3.png");
		boom1_2->setPosition(boom1_2->getPosition() - Vec2(100, 60));
		this->addChild(boom1_2);
	});

	boom1_1->runAction(Sequence::create(moveBy, boomDone, NULL));
}
