#include "SocialLayer.h"
#include "MainUIScene/FriendListLayer.h"

SocialLayer::SocialLayer(void)
{
}


SocialLayer::~SocialLayer(void)
{
}

bool SocialLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initframe();
	initTitle();
	return true;
}

void SocialLayer::initframe()
{
	Size size = Director::getInstance()->getVisibleSize();

	auto listbase = Sprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(size.width/2, 410);
	this->addChild(listbase);

	initList();

	//背景
	auto background = Sprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(size.width/2, 760);
	this->addChild(background);

	//底部背景
	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);
	this->addChild(bottom_list);

	auto friend_max_bk = Sprite::createWithSpriteFrameName("firend_curtain.jpg");
	friend_max_bk->setPosition(size.width/2, 620);
	friend_max_bk->setScale(1.4f);
	this->addChild(friend_max_bk);

	//顶部的文字
	auto friend_max_text = Sprite::createWithSpriteFrameName("text_friend_number.png");
	friend_max_text->setPosition(80, 30);
	friend_max_text->setScale(0.8f);
	friend_max_bk->addChild(friend_max_text);

	auto friend_max = LabelTTF::create("90/99", "Arial", 20);
	friend_max->setPosition(210, 30);
	friend_max_bk->addChild(friend_max);

	//顶部文字的背景
	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);

	//
	auto page_base = Sprite::create("ui/page_base.png");
	page_base->setPosition(45, 165);
	this->addChild(page_base);
	auto page_text = LabelTTF::create("1/1", "Arial", 25);
	page_text->setPosition(45, 25);
	page_base->addChild(page_text);
}

void SocialLayer::initTitle()
{
	Size size = Director::getInstance()->getVisibleSize();

	//顶部文字
	auto title_myfriend = Sprite::createWithSpriteFrameName("pagename_myfriend.png");
	title_myfriend->setPosition(size.width/2, 690);
	this->addChild(title_myfriend);

	//添加好友
	auto button_right_normal = Sprite::createWithSpriteFrameName("button_left_0.png");
	auto button_right_pressed = Sprite::createWithSpriteFrameName("button_left_1.png");
	auto button_right_disable = Sprite::createWithSpriteFrameName("button_left_2.png");
	auto button_right_menuItem = MenuItemSprite::create(button_right_normal, button_right_pressed, button_right_disable);
	button_right_menuItem->setCallback([](Ref* pSender){
		log("Sale");

	});

	auto text_add = Sprite::createWithSpriteFrameName("text_add.png");
	text_add->setPosition(button_right_normal->getContentSize().width/2, button_right_normal->getContentSize().height/2);
	button_right_menuItem->addChild(text_add);

	auto menu_right = Menu::create(button_right_menuItem, NULL);
	menu_right->setPosition(size.width - button_right_normal->getContentSize().width /2 + 40, 687);
	this->addChild(menu_right);
}

void SocialLayer::initList()
{
	FriendListLayer* fridenList = FriendListLayer::create();
	fridenList->setPosition(20, 160);
	this->addChild(fridenList);
}
