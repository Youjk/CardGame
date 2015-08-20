#include "MyCardLayer.h"
#include "Utils/AppStringFile.h"
#include "Layer/MyCardListLayer.h"


MyCardLayer::MyCardLayer(void)
{
}


MyCardLayer::~MyCardLayer(void)
{
}

bool MyCardLayer::init()
{
	if (!Layer::init())
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
			NotificationCenter::getInstance()->postNotification("ReturnToMain");              
			break;        
			//¼àÌýmenu¼ü        
		case EventKeyboard::KeyCode::KEY_MENU:             
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backlistener, this);
	return true;
}

void MyCardLayer::initframe()
{
	Size size = Director::getInstance()->getVisibleSize();

	//ÎÒµÄÓ¢ÐÛ±³¾°
	auto listbase = Sprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(size.width/2, 140);
	this->addChild(listbase);

	initList();

	//±³¾°
	auto background = Sprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(size.width/2, 760);
	this->addChild(background);

	//µ×²¿±³¾°
	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);
	this->addChild(bottom_list);

	//¶¥²¿ÎÄ×ÖµÄ±³¾°
	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);

	//¶¥²¿µÄÎÄ×Ö
	auto titletext = Sprite::createWithSpriteFrameName("titlename_mycard.png");
	titletext->setPosition(size.width/2, 690);
	this->addChild(titletext);

	//¶¥²¿³öÊÛ°´Å¥
	auto button_right_normal = Sprite::createWithSpriteFrameName("button_left_0.png");
	auto button_right_pressed = Sprite::createWithSpriteFrameName("button_left_1.png");
	auto button_right_disable = Sprite::createWithSpriteFrameName("button_left_2.png");
	auto button_right_menuItem = MenuItemSprite::create(button_right_normal, button_right_pressed, button_right_disable);
	button_right_menuItem->setCallback([](Ref* pSender){
		log("Sale");
		
	});

	auto text_sale = Sprite::createWithSpriteFrameName("text_sale.png");
	text_sale->setPosition(button_right_normal->getContentSize().width/2 - 15, button_right_normal->getContentSize().height/2);
	button_right_menuItem->addChild(text_sale);

	auto menu_right = Menu::create(button_right_menuItem, NULL);
	menu_right->setPosition(size.width - button_right_menuItem->getContentSize().width /2 + 40, 687);
	this->addChild(menu_right);

	//¶¥²¿·µ»Ø°´Å¥
	auto button_left_normal = Sprite::createWithSpriteFrameName("button_left_0.png");
	auto button_left_pressed = Sprite::createWithSpriteFrameName("button_left_1.png");
	auto button_left_disable = Sprite::createWithSpriteFrameName("button_left_2.png");
	auto menuItem = MenuItemSprite::create(button_left_normal, button_left_pressed, button_left_disable);
	menuItem->setCallback([](Ref* pSender){
		log("return");
		NotificationCenter::getInstance()->postNotification("ReturnToMain");
	});

	auto text_return = Sprite::createWithSpriteFrameName("text_return.png");
	text_return->setPosition(button_left_normal->getContentSize().width/2 - 15, button_left_normal->getContentSize().height/2);
	menuItem->addChild(text_return);

	auto menu_left = Menu::create(menuItem, NULL);
	menu_left->setPosition(menuItem->getContentSize().width/2 - 10, 687);
	this->addChild(menu_left);
}

void MyCardLayer::initList()
{
	MyCardListLayer* mycardlist = MyCardListLayer::create();
	mycardlist->setPosition(20, 160);
	this->addChild(mycardlist);
}