#include "MainUILayer.h"
#include "Utils/AppStringFile.h"

MainUILayer::MainUILayer(void)
{
	m_curUI = MAIL_UI;
}


MainUILayer::~MainUILayer(void)
{
}

bool MainUILayer::init()
{
	if(!Layer::init())
	{
		return false;
	} 

	Size size = Director::getInstance()->getVisibleSize();

	//添加背景
	auto bg = Sprite::create("ui/background_1.jpg");
	bg->setPosition(size.width/2, size.height/2);
	bg->setScale(2.23f);
	this->addChild(bg);

	configureTeamUI();  //初始化成员UI
	configureMenuUI();  //初始化按钮UI

	//注册BMessage，如果收到，执行getMessage
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MainUILayer::return_callback), "ReturnToMain", NULL);
	
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

//配置队伍UI
void MainUILayer::configureTeamUI()
{
	Size size = Director::getInstance()->getVisibleSize();

	//队伍UI
	team = Sprite::createWithSpriteFrameName("team.png");
	team->setPosition(size.width/2, size.height - 320);
	this->addChild(team);
	auto text_myTeam = Sprite::createWithSpriteFrameName("titlename_team.png");
	text_myTeam->setPosition(text_myTeam->getContentSize().width / 2 - 40, team->getContentSize().height - 33);
	team->addChild(text_myTeam);

	//领导力UI
	auto text_leadship = Sprite::createWithSpriteFrameName("leadship.png");
	text_leadship->setPosition(text_leadship->getContentSize().width / 2 + 5, 35);
	team->addChild(text_leadship);
	auto leadship = LabelTTF::create("145/300", "Arial", 32);
	leadship->setPosition(150, 35);
	leadship->setAnchorPoint(Vec2(0, 0.5));
	team->addChild(leadship);

	//团队实力UI
	auto text_teamlv = Sprite::createWithSpriteFrameName("teamlv.png");
	text_teamlv->setPosition(text_leadship->getContentSize().width/2 + 290, 35);
	team->addChild(text_teamlv);
	auto teamlv = LabelTTF::create("100", "Arial", 32);
	teamlv->setPosition(450, 35);
	teamlv->setAnchorPoint(Vec2(0, 0.5));
	team->addChild(teamlv);

	//队长标志
	auto sign_captain = Sprite::createWithSpriteFrameName("sign_captain.png");
	sign_captain->setPosition(35, 215);
	team->addChild(sign_captain);

	//队长
	auto captain = Sprite::create("ui/littlecard_0001.png");
	captain->setPosition(97, 160);
	auto captain_fram = Sprite::createWithSpriteFrameName("littlecard_frame_class4_elite.png");
	captain_fram->setPosition(captain->getContentSize().width / 2, captain->getContentSize().height / 2);
	captain->addChild(captain_fram);
	team->addChild(captain);

	//max_text
	text_max[0] = Sprite::createWithSpriteFrameName("arenamain_max.png");
	text_max[0]->setPosition(97, 91);
	team->addChild(text_max[0]);
	text_level[0] = Node::create();
	auto text_lv_00 = Sprite::createWithSpriteFrameName("lv.png");
	text_lv_00->setPositionX(-15);
	text_level[0]->addChild(text_lv_00);
	auto text_lv_value_00 = LabelTTF::create("99", "Arial", 25);
	text_lv_value_00->setPositionX(25);
	text_level[0]->addChild(text_lv_value_00);
	text_level[0]->setPosition(97, 91);
	team->addChild(text_level[0]);
	text_level[0]->setVisible(false);

	//位置1
	auto teammate1_role = Sprite::create("ui/littlecard_0331.png");
	teammate1_role->setPosition(232, 160);
	auto teammate1_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class4_elite.png");
	teammate1_frame->setPosition(teammate1_role->getContentSize().width /2 , teammate1_role->getContentSize().height/2);
	teammate1_role->addChild(teammate1_frame);
	team->addChild(teammate1_role);
	text_max[1] = Sprite::createWithSpriteFrameName("arenamain_max.png");
	text_max[1]->setPosition(232, 91);
	team->addChild(text_max[1]);
	text_level[1] = Node::create();
	auto text_lv_01 = Sprite::createWithSpriteFrameName("lv.png");
	text_lv_01->setPositionX(-15);
	text_level[1]->addChild(text_lv_01);
	auto text_lv_value_01 = LabelTTF::create("99", "Arial", 25);
	text_lv_value_01->setPositionX(25);
	text_level[1]->addChild(text_lv_value_01);
	text_level[1]->setPosition(232, 91);
	team->addChild(text_level[1]);
	text_level[1]->setVisible(false);

	//位置2
	auto teammate2_role = Sprite::create("ui/littlecard_0333.png");
	teammate2_role->setPosition(339, 160);
	auto teammate2_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class4_elite.png");
	teammate2_frame->setPosition(teammate2_role->getContentSize().width /2 , teammate2_role->getContentSize().height/2);
	teammate2_role->addChild(teammate2_frame);
	team->addChild(teammate2_role);
	text_max[2] = Sprite::createWithSpriteFrameName("arenamain_max.png");
	text_max[2]->setPosition(339, 91);
	team->addChild(text_max[2]);
	text_level[2] = Node::create();
	auto text_lv_02 = Sprite::createWithSpriteFrameName("lv.png");
	text_lv_02->setPositionX(-15);
	text_level[2]->addChild(text_lv_02);
	auto text_lv_value_02 = LabelTTF::create("99", "Arial", 25);
	text_lv_value_02->setPositionX(25);
	text_level[2]->addChild(text_lv_value_02);
	text_level[2]->setPosition(339, 91);
	team->addChild(text_level[2]);
	text_level[2]->setVisible(false);

	//位置3
	auto teammate3_role = Sprite::create("ui/littlecard_0355.png");
	teammate3_role->setPosition(446, 160);
	auto teammate3_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class4_elite.png");
	teammate3_frame->setPosition(teammate3_role->getContentSize().width /2 , teammate3_role->getContentSize().height/2);
	teammate3_role->addChild(teammate3_frame);
	team->addChild(teammate3_role);
	text_max[3] = Sprite::createWithSpriteFrameName("arenamain_max.png");
	text_max[3]->setPosition(446, 91);
	team->addChild(text_max[3]);
	text_level[3] = Node::create();
	auto text_lv_03 = Sprite::createWithSpriteFrameName("lv.png");
	text_lv_03->setPositionX(-15);
	text_level[3]->addChild(text_lv_03);
	auto text_lv_value_03 = LabelTTF::create("99", "Arial", 25);
	text_lv_value_03->setPositionX(25);
	text_level[3]->addChild(text_lv_value_03);
	text_level[3]->setPosition(446, 91);
	team->addChild(text_level[3]);
	text_level[3]->setVisible(false);

	//位置4
	auto teammate4_role = Sprite::create("ui/littlecard_0415.png");
	teammate4_role->setPosition(553, 160);
	auto teammate4_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class4_elite.png");
	teammate4_frame->setPosition(teammate4_role->getContentSize().width /2 , teammate4_role->getContentSize().height/2);
	teammate4_role->addChild(teammate4_frame);
	team->addChild(teammate4_role);
	text_max[4] = Sprite::createWithSpriteFrameName("arenamain_max.png");
	text_max[4]->setPosition(553, 91);
	team->addChild(text_max[4]);
	text_level[4] = Node::create();
	auto text_lv_04 = Sprite::createWithSpriteFrameName("lv.png");
	text_lv_04->setPositionX(-15);
	text_level[4]->addChild(text_lv_04);
	auto text_lv_value_04 = LabelTTF::create("99", "Arial", 25);
	text_lv_value_04->setPositionX(25);
	text_level[4]->addChild(text_lv_value_04);
	text_level[4]->setPosition(553, 91);
	team->addChild(text_level[4]);
	text_level[4]->setVisible(false);

	//邮箱UI
	auto normal_mail = Sprite::createWithSpriteFrameName("state_mail.png");
	auto menuItem = MenuItemSprite::create(normal_mail, normal_mail, normal_mail, CC_CALLBACK_1(MainUILayer::menu_mail_callback,this));
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(550, 270);
	team->addChild(menu);

	//闪烁动画
	this->schedule(SEL_SCHEDULE(&MainUILayer::textlevel_flash), 1.0f);
}

void MainUILayer::return_callback(Ref* pSender)
{
	restoreToMainUI();
}

//返回到主界面
void MainUILayer::restoreToMainUI()
{
	//this->addChild(team);
	//this->addChild(menu);
	switch (m_curUI)
	{
	case MAIN_UI:
		break;
	case CARD_UI:
		this->removeChild(_cardLayer);
		break;
	case SALE_UI:
		break;
	case EVOLVE_UI:
		this->removeChild(_cardEvolution);
		break;
	case LEVEL_IP_UI:
		this->removeChild(_cardLevelUpLayer);
		break;
	case TASK_UI:
		this->removeChild(_taskLayer);
		break;
	case COLLEAGE_UI:
		this->removeChild(_colleageLayer);
		break;
	case MAIL_UI:
		this->removeChild(_mailLayer);
		break;
	case CHIP_UI:
		this->removeChild(_chipLayer);
	default:
		break;
	}
	if (m_curUI != MAIL_UI)
	{
		configureTeamUI();
		configureMenuUI();
		m_curUI = MAIL_UI;
	}
}

void  MainUILayer::removeMainUI()
{
	this->unscheduleAllCallbacks();
	this->removeChild(team);
	this->removeChild(menu);
}

//邮箱按钮点击回调
void MainUILayer::menu_mail_callback(Ref* pSender)
{
	log("menuMail touched");
	removeMainUI();
	showMailUI();
}

//显示邮箱UI界面
void MainUILayer::showMailUI()
{
	m_curUI = MAIL_UI;
	_mailLayer = MailLayer::create();
	this->addChild(_mailLayer);
}

//配置菜单的UI
void MainUILayer::configureMenuUI()
{
	Size size = Director::getInstance()->getVisibleSize();
	menu = Node::create();
	this->addChild(menu);

	//英雄
	auto card_item = createMenuItem("button_little_", "text_card.png");
	card_item->setCallback([this](Ref* pSender){
		log("hero menu");
		removeMainUI();
		showCardUI();
	});

	//进化
	auto cardevolve_item = createMenuItem("button_little_", "text_cardevolve.png");
	cardevolve_item->setCallback([this](Ref* pSender){
		log("evolute menu");
		removeMainUI();
		showCardEvolveUI();
	});

	//第一排菜单
	auto menu_row1 = Menu::create(card_item, cardevolve_item, NULL);
	menu_row1->alignItemsHorizontallyWithPadding(30);
	menu_row1->setPosition(size.width /2, size.height/2 - 70);
	menu->addChild(menu_row1);

	//碎片
	auto chip_item = createMenuItem("button_little_", "text_chip.png");
	chip_item->setCallback([this](Ref* pSender){
		log("chip menu");
		removeMainUI();
		showChipUI();
	});

	//升级
	auto mix_item = createMenuItem("button_little_", "text_mix.png");
	mix_item->setCallback([this](Ref* pSender){
		log("mix menu");
		removeMainUI();
		showCardLevelupUI();
	});

	//第二排菜单
	auto menu_row2 = Menu::create(chip_item, mix_item, NULL);
	menu_row2->alignItemsHorizontallyWithPadding(30);
	menu_row2->setPosition(size.width /2, size.height/2 - 175);
	menu->addChild(menu_row2);

	//奖励
	auto task_item = createMenuItem("button_little_", "text_tast.png");
	task_item->setCallback([this](Ref* pSender){
		log("task menu");
		removeMainUI();
		showTaskUI();
	});

	//技能学院
	auto colleage_item = createMenuItem("button_little_", "text_colleage.png");
	colleage_item->setCallback([this](Ref* pSender){
		log("college menu");
		removeMainUI();
		showColleageUI();
	});

	//第一排菜单
	auto menu_row3 = Menu::create(task_item, colleage_item, NULL);
	menu_row3->alignItemsHorizontallyWithPadding(30);
	menu_row3->setPosition(size.width /2, size.height/2 - 280);
	menu->addChild(menu_row3);
	
}

MenuItemSprite* MainUILayer::createMenuItem(std::string spritename, std::string textname)
{
	auto normal = Sprite::createWithSpriteFrameName(spritename + "0.png");
	auto select = Sprite::createWithSpriteFrameName(spritename + "1.png");
	auto disable = Sprite::createWithSpriteFrameName(spritename + "2.png");
		
	auto text = Sprite::createWithSpriteFrameName(textname);
	text->setPosition(normal->getContentSize().width / 2, normal->getContentSize().height / 2);
	MenuItemSprite* menuItem = MenuItemSprite::create(normal, select, disable);
	menuItem->addChild(text);

	return menuItem;
}


 //显示英雄界面
void MainUILayer::showCardUI()
{
	log("show hero scene");
	m_curUI = CARD_UI;
	_cardLayer =MyCardLayer::create();
	this->addChild(_cardLayer);
}

//显示进化界面
void MainUILayer::showCardEvolveUI() 
{
	log("show evolution scene");
	_cardEvolution = CardEvolution::create();
	this->addChild(_cardEvolution);
	m_curUI = EVOLVE_UI;
}

 //显示碎片界面
void MainUILayer::showChipUI() 
{
	log("show chip scene");
	
	m_curUI = CHIP_UI;
	_chipLayer = MyChipLayer::create();
	this->addChild(_chipLayer);
}

//显示卡牌升级界面
void MainUILayer::showCardLevelupUI()
{
	log("show level_up scene");
	m_curUI = LEVEL_IP_UI;
	_cardLevelUpLayer = CardLevelUpLayer::create();
	this->addChild(_cardLevelUpLayer);
}

 //显示技能学院界面
void MainUILayer::showColleageUI()
{
	log("show colleage scene");
	m_curUI = COLLEAGE_UI;
	_colleageLayer = ColleageLayer::create();
	this->addChild(_colleageLayer);
}

//显示奖励界面
void MainUILayer::showTaskUI() 
{
	m_curUI = TASK_UI;
	_taskLayer = TaskLayer::create();
	this->addChild(_taskLayer);
	log("show task scene");
}

void MainUILayer::textlevel_flash(float dt)
{
	for (int i = 0; i < 5; ++i)
	{
		if(text_max[i]->isVisible())
		{
			text_max[i]->setVisible(false);
			text_level[i]->setVisible(true);
		}
		else{
			text_max[i]->setVisible(true);
			text_level[i]->setVisible(false);
		}
	}
}