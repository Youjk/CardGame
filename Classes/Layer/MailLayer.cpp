#include "MailLayer.h"


MailLayer::MailLayer(void)
{
}


MailLayer::~MailLayer(void)
{
}

bool MailLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	initframe();

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

void MailLayer::initframe()
{
	Size size = Director::getInstance()->getVisibleSize();

	//±³¾°
	auto bg = Sprite::create("ui/background_2.jpg");
	bg->setScale(1.26f);
	bg->setPosition(size.width/2, 760);
	this->addChild(bg);

	//µ×²¿±³¾°
	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);
	this->addChild(bottom_list);

	//ÖÐ¼äµÄ±³¾°
	auto listbase = Sprite::create("ui/listbase_1.jpg");
	listbase->setScaleX(1.4f);
	listbase->setPosition(size.width/2, 410);
	this->addChild(listbase);

	//¶¥²¿ÎÄ×ÖµÄ±³¾°
	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);

	//¶¥²¿µÄÎÄ×Ö

	auto titletext = Sprite::createWithSpriteFrameName("titlename_mail.png");
	titletext->setPosition(size.width/2, 690);
	this->addChild(titletext);

	//·µ»Ø°´Å¥
	auto button_left_normal = Sprite::createWithSpriteFrameName("button_left_0.png");
	auto button_left_pressed = Sprite::createWithSpriteFrameName("button_left_1.png");
	auto button_left_disable = Sprite::createWithSpriteFrameName("button_left_2.png");
	auto menuItem = MenuItemSprite::create(button_left_normal, button_left_pressed, button_left_disable);
	menuItem->setCallback([](Ref* pSender){
			log("return");
			NotificationCenter::getInstance()->postNotification("ReturnToMain");
	});
	
	auto text_return = Sprite::createWithSpriteFrameName("text_return.png");
	text_return->setPosition(button_left_normal->getContentSize().width/2, button_left_normal->getContentSize().height/2);
	menuItem->addChild(text_return);

	auto menu_left = Menu::create(menuItem, NULL);
	menu_left->setPosition(menuItem->getContentSize().width/2 - 10, 687);
	this->addChild(menu_left);
}