#include "MyChipLayer.h"
#include "Layer/MyChipLayerList.h"

MyChipLayer::MyChipLayer(void)
{
}


MyChipLayer::~MyChipLayer(void)
{
}

bool MyChipLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initframe();
	initList();

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

void MyChipLayer::initframe()
{
	Size size = Director::getInstance()->getVisibleSize();


	//±³¾°
	auto background = Sprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(size.width/2, 760);
	this->addChild(background);

	//ËéÆ¬±³¾°
	auto listbase = Sprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(size.width/2, 410);
	this->addChild(listbase);

	//ListView
	initList();

	//µ×²¿±³¾°
	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);
	this->addChild(bottom_list);

	//¶¥²¿ÎÄ×ÖµÄ±³¾°
	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);

	//¶¥²¿µÄÎÄ×Ö
	auto titletext = Sprite::createWithSpriteFrameName("titlename_chip.png");
	titletext->setPosition(size.width/2, 690);
	this->addChild(titletext);

	//·Ö½âËéÆ¬°´Å¥
	auto button_right_normal = Sprite::createWithSpriteFrameName("button_right_0.png");
	auto button_right_pressed = Sprite::createWithSpriteFrameName("button_right_1.png");
	auto button_right_disable = Sprite::createWithSpriteFrameName("button_right_2.png");
	auto right_menuItem = MenuItemSprite::create(button_right_normal, button_right_pressed, button_right_disable);
	right_menuItem->setCallback([](Ref* pSender){
		log("break");
	});

	auto text_break = Sprite::createWithSpriteFrameName("text_break.png");
	text_break->setPosition(button_right_normal->getContentSize().width/2 + 15,button_right_normal->getContentSize().height/2);
	right_menuItem->addChild(text_break);

	auto menu_right = Menu::create(right_menuItem, NULL);
	menu_right->setPosition(size.width - right_menuItem->getContentSize().width/2 + 10, 687);
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

	//ºÏ³ÉËéÆ¬ÏÂÃæÄÇ¸öºÚ¿ò±³¾°
	auto chip_max_bg = Sprite::createWithSpriteFrameName("firend_curtain.jpg");
	chip_max_bg->setScale(1.4f);
	chip_max_bg->setPosition(size.width/2, 620);
	this->addChild(chip_max_bg);

	//ºÚ¿òÉÏºÏ³ÉËéÆ¬ÎÄ×Ö
	auto chip_max_text = Sprite::createWithSpriteFrameName("text_omnipotence.png");
	chip_max_text->setScale(0.8f);
	chip_max_text->setPosition(80, 30);
	chip_max_bg->addChild(chip_max_text);

	auto chip_max = LabelTTF::create("50", "Arial", 20);
	chip_max->setPosition(210, 30);
	chip_max_bg->addChild(chip_max);


}

void MyChipLayer::initList()
{
	MyChipLayerList* chipList =MyChipLayerList::create();
	this->addChild(chipList);
	chipList->setPosition(20, 80);
}
