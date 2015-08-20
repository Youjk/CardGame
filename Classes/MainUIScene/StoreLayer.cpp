#include "StoreLayer.h"
#include "Utils/AppStringFile.h"
#include "Dialog/DialogLayer.h"
#include "MainUIScene/RaffleOneLayer.h"
#include "MainUIScene/RaffleTenLayer.h"

USING_NS_CC;


StoreLayer::StoreLayer(void)
{
}


StoreLayer::~StoreLayer(void)
{
}

bool StoreLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initFrame();
	initMenu();
	initTitle();
	return true;
}

void StoreLayer::initFrame()
{
	Size size = Director::getInstance()->getVisibleSize();


	//背景
	auto background = Sprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(size.width/2, 760);
	this->addChild(background);

	//奖励背景
	auto listbase = Sprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(size.width/2, 410);
	this->addChild(listbase);

	//底部背景
	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);
	this->addChild(bottom_list);

	//顶部文字的背景
	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);
}


void StoreLayer::initTitle()
{
	Size size =  Director::getInstance()->getVisibleSize();

	//顶部文字
	auto title_store = Sprite::createWithSpriteFrameName("titlename_store.png");
	title_store->setPosition(size.width/2, 690);
	this->addChild(title_store);

	//充值按钮
	auto button_right_normal = Sprite::createWithSpriteFrameName("button_right_0.png");
	auto button_right_pressed = Sprite::createWithSpriteFrameName("button_right_1.png");
	auto button_right_selected = Sprite::createWithSpriteFrameName("button_right_2.png");

	auto menuItem = MenuItemSprite::create(button_right_normal, button_right_pressed, button_right_selected);
	auto text_raffle = Sprite::createWithSpriteFrameName("text_raffle.png");
	text_raffle->setPosition(button_right_normal->getContentSize().width/2 + 10, button_right_normal->getContentSize().height/2);
	menuItem->addChild(text_raffle);
	menuItem->setCallback([](Ref* pSender){

	});

	auto menu_right = Menu::create(menuItem, NULL);
	this->addChild(menu_right);
	menu_right->setPosition(size.width - menuItem->getContentSize().width/2 + 10, 687);

}

void StoreLayer::initMenu()
{
	Size size = Director::getInstance()->getVisibleSize();
	menu = Node::create();
	this->addChild(menu);
	//友情抽奖
	auto raffle_friend_Item = createMenuItem("raffle_friend.png");
	raffle_friend_Item->setCallback([](Ref* pSender){
		Director::getInstance()->pushScene(RaffleOneLayer::createScene());
	});

	//宝石抽奖
	auto raffle_diamond_Item = createMenuItem("raffle_diamond.png");
	raffle_diamond_Item->setCallback([](Ref* pSender){
		Director::getInstance()->pushScene(RaffleTenLayer::createScene());
	});


	//第一排菜单
	auto menu_row1 = Menu::create(raffle_friend_Item, raffle_diamond_Item, NULL);
	menu_row1->alignItemsHorizontallyWithPadding(30);
	menu_row1->setPosition(size.width/2, size.height/2 + 110);
	menu->addChild(menu_row1);

	//购买体力
	auto  buy_str_Item = createMenuItem("text_buy_str.png");
	buy_str_Item->setCallback([this](Ref* pSender){
		createDialog("store_buy_str");
	});


	//购买背包
	auto buy_bag_Item = createMenuItem("text_buy_bag.png");
	buy_bag_Item->setCallback([this](Ref* pSender){
		createDialog("store_buy_bag");
	});

	//第二排菜单
	auto menu_row2 = Menu::create(buy_str_Item, buy_bag_Item, NULL);
	menu_row2->alignItemsHorizontallyWithPadding(30);
	menu_row2->setPosition(size.width/2, size.height/2 + 10);
	menu->addChild(menu_row2);

	//购买PVP
	auto buy_pvp_item = createMenuItem("text_buy_pvp.png");
	buy_pvp_item->setCallback([](Ref* pSender){

	});
	
	//好友上限
	auto friend_number_Item = createMenuItem("text_friend_number.png");
	friend_number_Item->setCallback([this](Ref* pSender){
		createDialog("store_friend_number");
	});

	auto menu_row3 = Menu::create(buy_pvp_item, friend_number_Item, NULL);
	menu_row3->alignItemsHorizontallyWithPadding(30);
	menu_row3->setPosition(size.width/2, size.height/2 - 90);
	menu->addChild(menu_row3);

	//广告
	auto raffle_ad = Sprite::create("ui/raffle_ad.png");
	raffle_ad->setPosition(size.width/2, size.height/2-220);
	menu->addChild(raffle_ad);
}

MenuItemSprite * StoreLayer::createMenuItem(std::string textname)
{
	auto button_normal = Sprite::createWithSpriteFrameName("button_little_0.png");
	auto button_pressed = Sprite::createWithSpriteFrameName("button_little_1.png");
	auto button_selected = Sprite::createWithSpriteFrameName("button_little_2.png");

	auto menuItem = MenuItemSprite::create(button_normal, button_pressed, button_selected);
	auto text = Sprite::createWithSpriteFrameName(textname);
	text->setPosition(button_normal->getContentSize().width/2, button_normal->getContentSize().height/2);
	menuItem->addChild(text);

	return menuItem;
}

void StoreLayer::createDialog(std::string titlename)
{
	//弹出对话框
	DialogLayer* d = DialogLayer::create(Sprite::createWithSpriteFrameName("tipsbase.png"));
	d->setContentSize(Size(400, 200));
	d->setContentText(AppStringFile::getInstance()->getStringForKey(titlename).c_str());
	d->addButton("ok", 
		Sprite::createWithSpriteFrameName("button_0.png"),
		Sprite::createWithSpriteFrameName("button_2.png"),
		Sprite::createWithSpriteFrameName("button_2.png"),
		[d](Ref* pSender){
			d->removeFromParent();
	},0);
	Director::getInstance()->getRunningScene()->addChild(d);
}