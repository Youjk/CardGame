#include "MoreLayer.h"
#include "MainUIScene/MoreListLayer.h"

MoreLayer::MoreLayer(void)
{
}


MoreLayer::~MoreLayer(void)
{
}

bool MoreLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initframe();
	initTitle();
	return true;
}

void MoreLayer::initframe()
{
	Size size = Director::getInstance()->getVisibleSize();

	auto listbase = Sprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(size.width/2, 410);
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
}

void MoreLayer::initList()
{
	MoreListLayer* fridenList = MoreListLayer::create();
	fridenList->setPosition(20, 160);
	this->addChild(fridenList);
}

void MoreLayer::initTitle()
{
	Size size = Director::getInstance()->getVisibleSize();

	auto title_menu = Sprite::createWithSpriteFrameName("titlename_menu.png");
	title_menu->setPosition(size.width/2, 690);
	this->addChild(title_menu);
}
