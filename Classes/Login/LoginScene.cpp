#include "LoginScene.h"
#include "LoadingStoryAnimation/StoryScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif


LoginScene::LoginScene(void)
{
}


LoginScene::~LoginScene(void)
{
}

Scene* LoginScene::createScene()
{
	Scene* scene = Scene::create();

	auto layer = LoginScene::create();
	scene->addChild(layer);
	return scene;
}


bool LoginScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	initUI();

	auto backlistener = EventListenerKeyboard::create();
	backlistener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){
		switch(keyCode)
		{        
			//�������ؼ�        
		case EventKeyboard::KeyCode::KEY_ESCAPE:              
			Director::getInstance()->popScene();            
			break;        
			//����menu��        
		case EventKeyboard::KeyCode::KEY_MENU:             
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backlistener, this);
	return true;
}

void LoginScene::initUI()
{
	Size visibleSize = Director::getInstance()->getWinSize();

	//����background
	Sprite* background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_bei.png"));
	background->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(background);
	background->setScale(1.877f);

	//����logo
	Sprite* logo = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_logo.png"));
	logo->setPosition(logo->getContentSize().width/2, visibleSize.height - logo->getContentSize().height / 2 - 10);
	this->addChild(logo);

	//���ش�С��
	Sprite* dajiaojie = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_daxiaojie.png"));
	dajiaojie->setAnchorPoint(Vec2(1, 0));
	dajiaojie->setPosition( visibleSize.width + dajiaojie->getContentSize().width, visibleSize.height/2*0.8);
	this->addChild(dajiaojie);
	//����
	dajiaojie->runAction(MoveBy::create(0.2f, Vec2(-dajiaojie->getContentSize().width, 0)));

	//����ɵ��
	Sprite* shaman = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_shaman.png"));
	shaman->setAnchorPoint(Vec2(0, 1));
	shaman->setPosition(-shaman->getContentSize().width, visibleSize.height/2*1.2);
	this->addChild(shaman);
	//����
	shaman->runAction(MoveBy::create(0.2f, Vec2(shaman->getContentSize().width, 0)));

	//�汾��
	auto version = Label::createWithBMFont("fonts/ziti_2.fnt", "v1.2.2");
	version->setPosition(version->getContentSize().width/2, visibleSize.height - version->getContentSize().height/2);
	this->addChild(version);

	//�ڿ�
	auto fff  = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_fff.png"));
	fff->setPosition(visibleSize.width/2, fff->getContentSize().height/2);
	fff->setScaleX(10.57f);
	this->addChild(fff);

	//�ײ�����
	auto wenzi = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_y.png"));
	wenzi->setPosition(visibleSize.width/2, wenzi->getContentSize().height/2 + 7);
	this->addChild(wenzi);

	//��ɢЧ��
	auto suduxian = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_suduxian.png"));
	suduxian->setPosition(visibleSize.width/2, visibleSize.height/2);
	suduxian->setScale(1.877f);
	this->addChild(suduxian);

	//��ʼ��Ϸ����
	auto startGameBackground = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_textbase.png"));
	startGameBackground->setScale(1.877f);
	startGameBackground->setPosition(visibleSize.width/2,130);
	this->addChild(startGameBackground);
	
	//��ʼ����
	Sprite* startGame = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Textrue_stargame.png"));
	//auto startSelected = 
	auto enterGameItem = MenuItemSprite::create(startGame, startGame, CC_CALLBACK_1(LoginScene::startGameMenuCallback, this));
	enterGameItem->setPosition(visibleSize.width/2, 115.0f);
	auto enterGameMenu = Menu::create(enterGameItem, NULL);
	enterGameMenu->setPosition(Point::ZERO);
	this->addChild(enterGameMenu);

	//��ť����
	auto scaleBig = ScaleTo::create(0.3f, 1.02f);
	auto scaleLitter = ScaleTo::create(0.3f, 1.0f);
	auto sequence = Sequence::create(scaleBig, scaleLitter, NULL);
	enterGameMenu->runAction(RepeatForever::create(sequence));
}

void LoginScene::initWebView()
{

}

void LoginScene::startGameMenuCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(StoryScene::createScene());
}