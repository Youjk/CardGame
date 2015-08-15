#include "FightLayer.h"
#include "Utils/AppStringFile.h"


FightLayer::FightLayer(void)
{
	m_times = 10;
	m_hp_time = 0;
	m_atktimes = 0;
}


FightLayer::~FightLayer(void)
{
}

bool FightLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initFrame();
	initContent();
	initTitle();
	initInfo();
	return true;
}

void FightLayer::initFrame()
{
	Size size = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(size.width/2, 760);
	this->addChild(background);

	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);;
	this->addChild(bottom_list);

	auto listbase = Sprite::create("ui/arenabase.jpg");
	listbase->setScaleX(1.4f);
	listbase->setPosition(size.width/2, 410);
	this->addChild(listbase);

	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);
}

void FightLayer::initContent()
{
	Size size = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; j++)
		{
			auto normal_button = Sprite::createWithSpriteFrameName("button_arena_0.png");
			auto proessed_button = Sprite::createWithSpriteFrameName("button_arena_1.png");   
			auto selected_button = Sprite::createWithSpriteFrameName("button_arena_2.png");  

			auto menuItem = MenuItemSprite::create(normal_button, proessed_button, selected_button);
			menuItem->setCallback([](Ref* pSender){

			});
			menuItem->setPosition(200 + 250 * i, 450 - 130 * j);
			auto menu = Menu::create(menuItem, NULL);
			menu->setPosition(Point::ZERO);
			this->addChild(menu);
		}
	}

	auto text_white = Sprite::createWithSpriteFrameName("text_arena_white.png");
	text_white->setPosition(200, 450);
	this->addChild(text_white);

	auto text_green = Sprite::createWithSpriteFrameName("text_arena_green.png");
	text_green->setPosition(450, 450);
	this->addChild(text_green);

	auto text_blue = Sprite::createWithSpriteFrameName("text_arena_blue.png");
	text_blue->setPosition(200, 320);
	this->addChild(text_blue);

	auto text_purple = Sprite::createWithSpriteFrameName("text_arena_purple.png");
	text_purple->setPosition(450, 320);
	this->addChild(text_purple);

	//ÊôÐÔ
	auto base = Sprite::create("ui/arenabase_01_16_9_02.png");
	base->setScaleX(50.0f);
	base->setPosition(320, 247);
	this->addChild(base);

	auto text_arenamain_hp = Sprite::createWithSpriteFrameName("text_arenamain_hp.png");
	text_arenamain_hp->setPosition(100, 247);
	this->addChild(text_arenamain_hp);

	emb_hp = LabelTTF::create("+0", "Arial", 25);
	emb_hp->setPosition(150, 247);
	this->addChild(emb_hp);

	//
	auto text_arenamain_atk = Sprite::createWithSpriteFrameName("text_arenamain_atk.png");
	text_arenamain_atk->setPosition(270, 247);
	this->addChild(text_arenamain_atk);

	emb_atk = LabelTTF::create("+0", "Arial", 25);
	emb_atk->setPosition(320, 247);
	this->addChild(emb_atk);

	//
	auto text_arenamain_time = Sprite::createWithSpriteFrameName("text_arenamain_time.png");
	text_arenamain_time->setPosition(440, 247);
	this->addChild(text_arenamain_time);

	emb_time = LabelTTF::create("10", "Arial", 25);
	emb_time->setPosition(480, 247);
	this->addChild(emb_time);

	//¹ÄÎèÉúÃü
	auto emb_hp_normal = Sprite::createWithSpriteFrameName("button_little_0.png");
	auto emb_hp_pressed = Sprite::createWithSpriteFrameName("button_little_1.png");
	auto emb_hp_disable = Sprite::createWithSpriteFrameName("button_little_2.png");
	emb_hp_Item = MenuItemSprite::create(emb_hp_normal, emb_hp_pressed, emb_hp_disable);
	emb_hp_Item->setCallback([this](Ref* pSender){
		if (m_times > 0)
		{
			m_times--;
			m_hp_time++;
			char p[5];
			sprintf(p, "+%d", m_hp_time);
			emb_hp->setString(p);
			sprintf(p, "%d", m_times);
			emb_time->setString(p);
		}else if(m_times <= 0)
		{
			emb_hp_Item->setEnabled(false);
			emb_atk_Item->setEnabled(false);
		}

	});

	auto text_emp_hp= Sprite::createWithSpriteFrameName("text_arenamain_emb_hp.png");
	text_emp_hp->setPosition(emb_hp_normal->getContentSize().width/2, emb_hp_normal->getContentSize().height/2);
	emb_hp_Item->addChild(text_emp_hp);

	//¹ÄÎè¹¥»÷
	auto emb_atk_normal = Sprite::createWithSpriteFrameName("button_little_0.png");
	auto emb_atk_pressed = Sprite::createWithSpriteFrameName("button_little_1.png");
	auto emb_atk_disable = Sprite::createWithSpriteFrameName("button_little_2.png");
	emb_atk_Item = MenuItemSprite::create(emb_atk_normal, emb_atk_pressed, emb_atk_disable);
	emb_atk_Item->setCallback([this](Ref* pSender){
		if (m_times > 0)
		{
			m_times--;
			m_atktimes++;
			char p[5];
			sprintf(p, "+%d", m_atktimes);
			emb_atk->setString(p);
			sprintf(p, "%d", m_times);
			emb_time->setString(p);
		}else if(m_times <= 0)
		{
			emb_hp_Item->setEnabled(false);
			emb_atk_Item->setEnabled(false);
		}

	});

	auto text_emp_atk= Sprite::createWithSpriteFrameName("text_arenamain_emb_atk.png");
	text_emp_atk->setPosition(emb_atk_normal->getContentSize().width/2, emb_atk_normal->getContentSize().height/2);
	emb_atk_Item->addChild(text_emp_atk);

	//ÅÅÁÐ²Ëµ¥
	auto menu = Menu::create(emb_hp_Item, emb_atk_Item, NULL);
	menu->alignItemsHorizontallyWithPadding(30);
	menu->setPosition(320, 190);
	this->addChild(menu);
}

void FightLayer::initTitle()
{
	Size size = Director::getInstance()->getVisibleSize();

	//¶¥²¿µÄÎÄ×Ö
	auto titletext = Sprite::createWithSpriteFrameName("titlename_arena.png");
	titletext->setPosition(size.width/2, 690);
	this->addChild(titletext);

	//Ë²Î»°´Å¥
	auto button_right_normal = Sprite::createWithSpriteFrameName("button_right_0.png");
	auto button_right_pressed = Sprite::createWithSpriteFrameName("button_right_1.png");
	auto button_right_disable = Sprite::createWithSpriteFrameName("button_right_2.png");
	auto button_right_menuItem = MenuItemSprite::create(button_right_normal, button_right_pressed, button_right_disable);
	button_right_menuItem->setCallback([](Ref* pSender){
		log("Sale");

	});

	auto text_sale = Sprite::createWithSpriteFrameName("text_rank.png");
	text_sale->setPosition(button_right_normal->getContentSize().width/2 - 15, button_right_normal->getContentSize().height/2);
	button_right_menuItem->addChild(text_sale);

	auto menu_right = Menu::create(button_right_menuItem, NULL);
	menu_right->setPosition(size.width - button_right_menuItem->getContentSize().width /2 + 65, 687);
	this->addChild(menu_right);
}

void FightLayer::initInfo()
{
	std::string strText;
	//
	auto rank_text = Sprite::createWithSpriteFrameName("text_arenamain_rank.png");
	rank_text->setAnchorPoint(Point::ZERO);
	rank_text->setPosition(-30, 610);
	this->addChild(rank_text);
	
	strText = AppStringFile::getInstance()->getStringForKey("fight_rank");

	auto rank = LabelTTF::create(strText, "Arial", 25);
	rank->setAnchorPoint(Point::ZERO);
	rank->setColor(Color3B(160, 32, 240));
	rank->setPosition(130, 615);
	this->addChild(rank);

	//
	auto victory_text = Sprite::createWithSpriteFrameName("text_arenamain_victory.png");
	victory_text->setAnchorPoint(Point::ZERO);
	victory_text->setPosition(200, 610);
	this->addChild(victory_text);

	strText = AppStringFile::getInstance()->getStringForKey("fight_victory");

	auto victory = LabelTTF::create(strText, "Arial", 25);
	victory->setAnchorPoint(Point::ZERO);
	victory->setPosition(360, 615);
	this->addChild(victory);

	//
	auto prestige_text = Sprite::createWithSpriteFrameName("text_arenamain_prestige.png");
	prestige_text->setAnchorPoint(Point::ZERO);
	prestige_text->setPosition(-30, 580);
	this->addChild(prestige_text);

	strText = AppStringFile::getInstance()->getStringForKey("fight_prestige");

	auto prestige = LabelTTF::create(strText, "Arial", 25);
	prestige->setAnchorPoint(Point::ZERO);
	prestige->setPosition(130, 585);
	this->addChild(prestige);

	//
	auto mark_text = Sprite::createWithSpriteFrameName("text_arenamain_mark.png");
	mark_text->setAnchorPoint(Point::ZERO);
	mark_text->setPosition(200, 580);
	this->addChild(mark_text);

	strText = AppStringFile::getInstance()->getStringForKey("fight_mark");

	auto mark = LabelTTF::create(strText, "Arial", 25);
	mark->setAnchorPoint(Point::ZERO);
	mark->setPosition(360, 585);
	this->addChild(mark);

	//
	auto times_text = Sprite::createWithSpriteFrameName("text_arenamain_times.png");
	times_text->setAnchorPoint(Point::ZERO);
	times_text->setPosition(14, 550);
	this->addChild(times_text);

	strText = AppStringFile::getInstance()->getStringForKey("fight_times");

	auto times = LabelTTF::create(strText, "Arial", 25);
	times->setAnchorPoint(Point::ZERO);
	times->setPosition(220, 555);
	this->addChild(times);

	//
	auto listbase = Sprite::createWithSpriteFrameName("listbase_3_16_9.png");
	listbase->setPosition(14, 540);
	this->addChild(listbase);
}