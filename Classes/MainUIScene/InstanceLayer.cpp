#include "InstanceLayer.h"
#include "BattleScene/BattleLayer.h"


InstanceLayer::InstanceLayer(void)
{
	m_pos_x[0] = m_pos_x[3] = 160;
	m_pos_x[1] = m_pos_x[4] = 320;
	m_pos_x[2] = m_pos_x[5] = 480;

	m_pos_y[0] = m_pos_y[1] = m_pos_y[2] = 550;
	m_pos_y[3] = m_pos_y[4] = m_pos_y[5] = 390;
		
	m_curUI = INSTANCE_UI;
	normalInstanceListLayer = NULL;;
}


InstanceLayer::~InstanceLayer(void)
{
}

bool InstanceLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(InstanceLayer::return_lineup), "ReturnLineup", NULL);
	initframe();

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

void InstanceLayer::initframe()
{
	Size size = Director::getInstance()->getVisibleSize();

	//中间背景
	listbase = Sprite::create("ui/listbase_1.jpg");
	listbase->setScaleX(1.4f);
	listbase->setPosition(size.width/2, 400);
	this->addChild(listbase, 1);

	initList();

	//顶部背景
	auto background = Sprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(size.width/2, 760);
	this->addChild(background, 3);

	//底部背景
	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);
	this->addChild(bottom_list, 3);

	initTitle();
}

void InstanceLayer::initTitle()
{
	Size size = Director::getInstance()->getVisibleSize();

	//顶部的文字
	title_custom_instance = Sprite::createWithSpriteFrameName("titlename_instance_custom.png");
	title_custom_instance->setPosition(size.width/2, 690);
	this->addChild(title_custom_instance, 4);

	//精英按钮
	auto button_left_normal = Sprite::createWithSpriteFrameName("button_left_0.png");
	auto button_left_pressed = Sprite::createWithSpriteFrameName("button_left_1.png");
	auto button_left_disable = Sprite::createWithSpriteFrameName("button_left_2.png");
	auto menuItem = MenuItemSprite::create(button_left_normal, button_left_pressed, button_left_disable);
	menuItem->setCallback([](Ref* pSender){
	
	});

	auto text_elite_install = Sprite::createWithSpriteFrameName("text_elite.png");
	text_elite_install->setPosition(button_left_normal->getContentSize().width/2 - 15, button_left_normal->getContentSize().height/2);
	menuItem->addChild(text_elite_install);

	menu_left = Menu::create(menuItem, NULL);
	menu_left->setPosition(menuItem->getContentSize().width/2 - 10, 687);
	this->addChild(menu_left, 4);

	//活动按钮
	auto button_right_normal = Sprite::createWithSpriteFrameName("button_left_0.png");
	auto button_right_pressed = Sprite::createWithSpriteFrameName("button_left_1.png");
	auto button_right_disable = Sprite::createWithSpriteFrameName("button_left_2.png");
	auto menu_rightItem = MenuItemSprite::create(button_right_normal, button_right_pressed, button_right_disable);
	menu_rightItem->setCallback([](Ref* pSender){
	
	});

	auto text_activity = Sprite::createWithSpriteFrameName("text_activity.png");
	text_activity->setPosition(button_right_normal->getContentSize().width/2 - 15, button_right_normal->getContentSize().height/2);
	menu_rightItem->addChild(text_activity);

	menu_right = Menu::create(menu_rightItem, NULL);
	menu_right->setPosition(size.width - button_right_normal->getContentSize().width/2 + 30, 687);
	this->addChild(menu_right);
}

void InstanceLayer::initList()
{
	normalInstanceListLayer = NormalInstanceListLayer::create();
	normalInstanceListLayer->setPosition(20, 160);
	this->addChild(normalInstanceListLayer, 2);
}

//返回到副本界面
void InstanceLayer::return_instance()
{
	if (title_custom_lineup)
	{
		this->removeChild(title_custom_lineup);
		title_custom_lineup = NULL;
	}
	this->removeChild(menu_left_new);
	this->removeChild(lineup_content);
	listbase->setTexture(TextureCache::getInstance()->addImage("ui/listbase_1.jpg"));
	initTitle();
	
	normalInstanceListLayer->setTouchEnabled(true);
	normalInstanceListLayer->setVisible(true);
	m_curUI = INSTANCE_UI;
}

//返回到战斗界面
void InstanceLayer::return_lineup(Ref* pSender)
{
	normalInstanceListLayer->setTouchEnabled(false);
	normalInstanceListLayer->setVisible(false);

	this->removeChild(title_custom_instance);
	this->removeChild(menu_left);
	this->removeChild(menu_right);
	listbase->setTexture(TextureCache::getInstance()->addImage("ui/confirmlinebase.jpg"));

	Size size = Director::getInstance()->getVisibleSize();
	//顶部文字
	title_custom_lineup = Sprite::createWithSpriteFrameName("titlename_lineup.png");
	title_custom_lineup->setPosition(size.width/2, 690);
	this->addChild(title_custom_lineup, 4);

	//精英按钮
	auto button_left_normal = Sprite::createWithSpriteFrameName("button_left_0.png");
	auto button_left_pressed = Sprite::createWithSpriteFrameName("button_left_1.png");
	auto button_left_disable = Sprite::createWithSpriteFrameName("button_left_2.png");
	auto menuItem = MenuItemSprite::create(button_left_normal, button_left_pressed, button_left_disable);
	menuItem->setCallback([this](Ref* pSender){
		return_instance();
	});

	auto text_elite_install = Sprite::createWithSpriteFrameName("text_return.png");
	text_elite_install->setPosition(button_left_normal->getContentSize().width/2 - 15, button_left_normal->getContentSize().height/2);
	menuItem->addChild(text_elite_install);

	menu_left_new = Menu::create(menuItem, NULL);
	menu_left_new->setPosition(menuItem->getContentSize().width/2 - 10, 687);
	this->addChild(menu_left_new, 4);

	//队形内容
	lineup_content = Node::create();

	for (int i = 0; i < 6; i++)
	{
		Node* card = Node::create();
		auto card_frame = Sprite::createWithSpriteFrameName("bigcard_frame_class4_elite.png");
		card->addChild(card_frame);

		char pHeroName[20];
		sprintf(pHeroName, "bigcard_03%02d.png", 29 + i * 2);
		auto card_content = Sprite::createWithSpriteFrameName(pHeroName);
		card->addChild(card_content);

		auto card_occupation_base = Sprite::createWithSpriteFrameName("icon_occupation_base_elite.png");
		card->addChild(card_occupation_base);

		Sprite* card_occupatuon;

		switch (i)
		{
		case 0:
			card_occupatuon = Sprite::createWithSpriteFrameName("icon_occupation_warrior_button.png");
			break;
		case 1:
			card_occupatuon = Sprite::createWithSpriteFrameName("icon_occupation_shaman_button.png");
			break;
		case 2:
			card_occupatuon = Sprite::createWithSpriteFrameName("icon_occupation_rogue_button.png");
			break;
		case 3:
			card_occupatuon = Sprite::createWithSpriteFrameName("icon_occupation_hunter_button.png");
			break;
		case 4:
			card_occupatuon = Sprite::createWithSpriteFrameName("icon_occupation_druid_button.png");
			break;
		case 5:
			card_occupatuon = Sprite::createWithSpriteFrameName("icon_occupation_mage_button.png");
			break;
		default:
			break;
		}
		card_occupatuon->setScale(2.0f);
		card_occupatuon->setPosition(61, -73);
		card->addChild(card_occupatuon);

		card->setScale(0.6f);
		card->setPosition(m_pos_x[i], m_pos_y[i]);
		lineup_content->addChild(card);
	}

	auto nameplate_captain = Sprite::createWithSpriteFrameName("nameplate_captain.png");
	nameplate_captain->setPosition(270, 460);
	lineup_content->addChild(nameplate_captain);

	auto nameplate_friend = Sprite::createWithSpriteFrameName("nameplate_friend.png");
	nameplate_friend->setPosition(440, 600);
	lineup_content->addChild(nameplate_friend);

	auto nameplate_captain_bottom = Sprite::createWithSpriteFrameName("nameplate_captain.png");
	nameplate_captain_bottom->setPosition(70, 280);
	lineup_content->addChild(nameplate_captain_bottom);

	auto text_captainskill_01 = Sprite::createWithSpriteFrameName("text_captainskill.png");
	text_captainskill_01->setPosition(140, 280);
	lineup_content->addChild(text_captainskill_01);

	std::string strtext;
	strtext = AppStringFile::getInstance()->getStringForKey("captain_skill");
	auto captain_skill_label = LabelTTF::create(strtext, "Arial", 20);
	captain_skill_label->setPosition(290, 280);
	lineup_content->addChild(captain_skill_label);

	auto nameplate_friend_bottom = Sprite::createWithSpriteFrameName("nameplate_friend.png");
	nameplate_friend_bottom->setPosition(70, 250);
	lineup_content->addChild(nameplate_friend_bottom);

	auto text_captainskill_02 = Sprite::createWithSpriteFrameName("text_captainskill.png");
	text_captainskill_02->setPosition(140, 250);
	lineup_content->addChild(text_captainskill_02);

	strtext = AppStringFile::getInstance()->getStringForKey("friend_skill");
	auto captain_friend_label = LabelTTF::create(strtext, "Arial", 20);
	captain_friend_label->setPosition(290, 250);
	lineup_content->addChild(captain_friend_label);

	//开始战斗按钮
	auto button_normal = Sprite::createWithSpriteFrameName("button_little_0.png");
	auto button_pressed = Sprite::createWithSpriteFrameName("button_little_1.png");
	auto button_disable = Sprite::createWithSpriteFrameName("button_little_2.png");
	auto button_Item = MenuItemSprite::create(button_normal, button_pressed, button_disable);
	button_Item->setCallback([](Ref* pSender){
		Director::getInstance()->pushScene(BattleLayer::createScene());
	});


	auto text_button = Sprite::createWithSpriteFrameName("text_starin.png");
	text_button->setPosition(button_normal->getContentSize().width/2, button_normal->getContentSize().height/2);
	button_Item->addChild(text_button);

	auto menu = Menu::create(button_Item, NULL);
	menu->setPosition(size.width/2, 190);
	lineup_content->addChild(menu);

	this->addChild(lineup_content, 5);
	m_curUI = LINEUP_UI;
}

//返回副本主页面
void InstanceLayer::call_by_main()
{
	if (m_curUI != INSTANCE_UI)
	{
		return_instance();
	}
}
