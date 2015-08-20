#include "CardLevelUpLayer.h"
#include "Utils/AppStringFile.h"


CardLevelUpLayer::CardLevelUpLayer(void)
{
}


CardLevelUpLayer::~CardLevelUpLayer(void)
{
}

bool CardLevelUpLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initframe();
	initcontent();

	auto backlistener = EventListenerKeyboard::create();
	backlistener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){
		switch(keyCode)
		{        
			//监听返回键        
		case EventKeyboard::KeyCode::KEY_ESCAPE:              
			NotificationCenter::getInstance()->postNotification("ReturnToMain");              
			break;        
			//监听menu键        
		case EventKeyboard::KeyCode::KEY_MENU:             
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backlistener, this);
	return true;
}

void CardLevelUpLayer::initframe()
{
	Size size = Director::getInstance()->getVisibleSize();

	//背景
	auto bg = Sprite::create("ui/background_2.jpg");
	bg->setScale(1.26f);
	bg->setPosition(size.width/2, 760);
	this->addChild(bg);

	//底部背景
	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);
	this->addChild(bottom_list);

	//升级背景
	auto listbase = Sprite::create("ui/eatcardbase.jpg");  
	listbase->setScale(1.4f);
	listbase->setPosition(size.width/2, 410);
	this->addChild(listbase);

	//顶部文字的背景
	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);

	//顶部的文字
	auto titletext = Sprite::createWithSpriteFrameName("titlename_eatcard.png");
	titletext->setPosition(size.width/2, 690);
	this->addChild(titletext);

	//顶部返回按钮
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

	//英雄升级框
	card_levelup_base = Sprite::createWithSpriteFrameName("bigcard_empty.png");
	card_levelup_base->setPosition(size.width/2, 530);
	this->addChild(card_levelup_base);

	//英雄升级属性背景
	card_levelup_pro_base = Sprite::createWithSpriteFrameName("cardinfobase.png");
	card_levelup_pro_base->setPosition(size.width/2, 350);
	this->addChild(card_levelup_pro_base);

	//左边三排背景框
	left_eated_01_bk = Sprite::createWithSpriteFrameName("littlecard_empty.png");
	left_eated_02_bk = Sprite::createWithSpriteFrameName("littlecard_empty.png");
	left_eated_03_bk = Sprite::createWithSpriteFrameName("littlecard_empty.png");
	left_eated_01_bk->setPosition(120, 580);
	left_eated_02_bk->setPosition(120, 480);
	left_eated_03_bk->setPosition(120, 380);
	this->addChild(left_eated_01_bk);
	this->addChild(left_eated_02_bk);
	this->addChild(left_eated_03_bk);

	//右边三排背景框
	right_eated_01_bk = Sprite::createWithSpriteFrameName("littlecard_empty.png");
	right_eated_02_bk = Sprite::createWithSpriteFrameName("littlecard_empty.png");
	right_eated_03_bk = Sprite::createWithSpriteFrameName("littlecard_empty.png");
	right_eated_01_bk->setPosition(520, 580);
	right_eated_02_bk->setPosition(520, 480);
	right_eated_03_bk->setPosition(520, 380);
	this->addChild(right_eated_01_bk);
	this->addChild(right_eated_02_bk);
	this->addChild(right_eated_03_bk);

	//消耗值框
	need_eat_pro_base = Sprite::createWithSpriteFrameName("eatcard_base2.png");
	need_eat_pro_base->setScale(2.0f);
	need_eat_pro_base->setPosition(size.width/2, 245);
	this->addChild(need_eat_pro_base);

	//选择吞噬英雄按钮,将角色放入卡框里
	choose_food_Item = createMenuItem("button_little_", "text_food.png");
	choose_food_Item->setCallback(CC_CALLBACK_1(CardLevelUpLayer::choose_food_menucalback, this));
	choose_food_Item->setScale(0.8f);
	auto menu_choose_food = Menu::create(choose_food_Item, NULL);
	menu_choose_food->setPosition(size.width/2 - 150, 183);
	this->addChild(menu_choose_food);

	//升级按钮
	startlevel_Item = createMenuItem("button_little_", "text_stareat.png");
	startlevel_Item->setScale(0.8f);
	startlevel_Item->setCallback(CC_CALLBACK_1(CardLevelUpLayer::start_update_level_menucallback,this));
	auto menu_start_level = Menu::create(startlevel_Item, NULL);
	menu_start_level->setPosition(size.width/2 + 150, 183);
	this->addChild(menu_start_level);
	startlevel_Item->setEnabled(false);
}

//添加卡牌
void CardLevelUpLayer::initcontent()
{
	//卡牌
	card = Node::create();
	this->addChild(card);
	//卡牌框
	auto card_fram = Sprite::createWithSpriteFrameName("bigcard_frame_class4_elite.png");
	card->addChild(card_fram);
	
	//卡牌人物
	auto card_content = Sprite::createWithSpriteFrameName("bigcard_0349.png");
	card->addChild(card_content);

	auto card_occupation_elite = Sprite::createWithSpriteFrameName("icon_occupation_base_elite.png");
	card_occupation_elite->setScale(0.8f);
	card_occupation_elite->setPosition(15, -20);
	card->addChild(card_occupation_elite);

	auto occupaction_warrior = Sprite::createWithSpriteFrameName("icon_occupation_warrior_button.png");
	occupaction_warrior->setPosition(65, -78);
	card->addChild(occupaction_warrior);
	card->setPosition(320, 530);

	//+号
	for (int i = 0; i < 3; ++i)
	{
		add[i] = Sprite::createWithSpriteFrameName("add.png");
		add[i]->setPosition(145, 605 - i * 100);
		this->addChild(add[i]);
		add[i]->runAction(RepeatForever::create(Blink::create(3.0, 5)));
	}
	for (int i = 3;i < 6; ++i)
	{
		add[i] = Sprite::createWithSpriteFrameName("add.png");
		add[i]->setPosition(545, 605 - (i - 3) * 100);
		this->addChild(add[i]);
		add[i]->runAction(RepeatForever::create(Blink::create(3.0, 5)));
	}

	//属性
	//生命title
	std::string strtext = AppStringFile::getInstance()->getStringForKey("levelup_life_text");
	auto life_text = LabelTTF::create(strtext, "Arial", 18);
	life_text->setPosition(280, 400);
	this->addChild(life_text);

	//生命值
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_life");
	auto life = LabelTTF::create(strtext, "Arial", 18);
	life->setPosition(350, 400);
	this->addChild(life);

	//攻击title
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_attack_text");
	auto attack_text = LabelTTF::create(strtext, "Arial", 18);
	attack_text->setPosition(280, 375);
	this->addChild(attack_text);

	//攻击值
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_attack");
	auto attack = LabelTTF::create(strtext, "Arial", 18);
	attack->setPosition(350, 375);
	this->addChild(attack);

	//等级image
	auto lvimage = Sprite::createWithSpriteFrameName("lvimage.png");
	lvimage->setPosition(255, 340);
	this->addChild(lvimage);

	//等级值
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_level");
	auto level = LabelTTF::create(strtext, "Arial", 25);
	level->setColor(Color3B(255, 255, 0));
	level->setPosition(255, 340);
	this->addChild(level);

	//技能名
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_skill_name_text");
	auto skill_name_text = LabelTTF::create(strtext, "Arial", 18);
	skill_name_text->setColor(Color3B(255, 255, 0));
	skill_name_text->setPosition(260, 300);
	this->addChild(skill_name_text);

	//技能等级
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_skill_level_text");
	auto skill_level_text = LabelTTF::create(strtext, "Arial", 18);;
	skill_level_text->setPosition(380, 300);
	this->addChild(skill_level_text);

	//技能值
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_skill_level_value");
	auto skill_level_value = LabelTTF::create(strtext, "Arial", 18);;
	skill_level_value->setPosition(410, 300);
	this->addChild(skill_level_value);

	//获得经验：
	auto getexp_text = Sprite::createWithSpriteFrameName("getexp.png");
	getexp_text->setPosition(130, 258);
	this->addChild(getexp_text);

	//消耗金币
	auto needcoin_text = Sprite::createWithSpriteFrameName("eatcard_money.png");
	needcoin_text->setPosition(130, 233);
	this->addChild(needcoin_text);

	//升级还需经验
	auto needexp_text = Sprite::createWithSpriteFrameName("eatcard_needexp.png");
	needexp_text->setPosition(400, 258);
	this->addChild(needexp_text);

	//技能升级几率
	auto skilleveluprate_text = Sprite::createWithSpriteFrameName("eatcard_skillupodds.png");
	 skilleveluprate_text->setPosition(400, 233);
	this->addChild(skilleveluprate_text);



	//进度条
	auto progress_bk = Sprite::create("ui/exp1_0.png");
	progress_bk->setPosition(286, 340);
	progress_bk->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(progress_bk);

}


MenuItemSprite* CardLevelUpLayer::createMenuItem(std::string spritename, std::string textname)
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

void CardLevelUpLayer::choose_food_menucalback(Ref* pSender)
{
	log("choose_food");

	Sprite* littlecard_frame[6];
	Sprite* littlecard_content[6];

	littlecard_content[0] = Sprite::create("ui/littlecard_0163.png");
	littlecard_content[1] = Sprite::create("ui/littlecard_0165.png");
	littlecard_content[2] = Sprite::create("ui/littlecard_0167.png");
	littlecard_content[3] = Sprite::create("ui/littlecard_0169.png");
	littlecard_content[4] = Sprite::create("ui/littlecard_0171.png");
	littlecard_content[5] = Sprite::create("ui/littlecard_0173.png");

	for (int i = 0; i < 6; ++i)
	{
		add[i]->setOpacity(0);
		littlecard_frame[i] = Sprite::createWithSpriteFrameName("littlecard_frame_class1.png");
		littlecard[i] = Node::create();
		littlecard[i]->addChild(littlecard_content[i]);
		littlecard[i]->addChild(littlecard_frame[i]);
		this->addChild(littlecard[i]);
		littlecard[i]->setScale(0.9f);
		if (i < 3)
		{
			littlecard[i]->setPosition(120, 580 - i * 100);
		}else{
			littlecard[i]->setPosition(520, 580 -(i- 3) * 100);
		}
	}

	//需求文本
	//所得经验数目
	std::string strtext = AppStringFile::getInstance()->getStringForKey("levelup_get_exp");
	get_xp = LabelTTF::create(strtext, "Arial", 18);
	get_xp->setPosition(210, 258);
	this->addChild(get_xp);

	//所需金币数
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_need_coin");
	need_coin = LabelTTF::create(strtext, "Arial", 18);
	need_coin->setPosition(210, 233);
	this->addChild(need_coin);

	//升级还需经验值
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_need_exp_before");
	need_xp= LabelTTF::create(strtext, "Arial", 18);
	need_xp->setPosition(510, 258);
	this->addChild(need_xp);

	//升级概率
	strtext = AppStringFile::getInstance()->getStringForKey("levelup_skill_level_value");
	auto chance= LabelTTF::create(strtext, "Arial", 18);
	chance->setPosition(510, 233);
	this->addChild(chance);

	//进度条边框
	progress_fr = Sprite::create("ui/exp1_2.png");
	progress_fr->setScaleX(0.6f);
	progress_fr->setAnchorPoint(Vec2(0, 0.5f));
	progress_fr->setPosition(290, 340);
	this->addChild(progress_fr);

	progress_fr->runAction(RepeatForever::create(Blink::create(3.0f, 5)));
	startlevel_Item->setEnabled(true);
}

void CardLevelUpLayer::start_update_level_menucallback(Ref* pSender)
{
	startlevel_Item->setEnabled(false);
	choose_food_Item->setEnabled(false);
	get_xp->setString("0");
	need_coin->setString("0");
	need_xp->setString(AppStringFile::getInstance()->getStringForKey("levelup_need_exp_after"));

	//动画
	auto littlecard_flash = Animation::create();

	for (int i = 17; i > 1; --i)
	{
		char name[30];
		sprintf(name, "eatcard_100%02d.png", i);
		//log(name);
		littlecard_flash->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	AnimationCache::getInstance()->addAnimation(littlecard_flash, "littlecard_flash");

	for (int i = 0; i < 6; ++i)
	{
		littlecard_flash_sprite[i] = Sprite::createWithSpriteFrameName("eatcard_10002.png");
		auto animate = Animate::create(littlecard_flash);
		auto spawan_flash = Spawn::create(animate, MoveTo::create(0.5f, Vec2(320, 530)), NULL);
		//做完所有动作，需要删除左右两边卡片和动画sprite
		auto flash_down =CallFuncN::create([this](Ref* pSender){

			auto flash_sprite = (Sprite*)pSender;
			this->removeChild(flash_sprite);
			for (int i = 0; i < 6; ++i)
			{
				this->removeChild(littlecard[i]);
				add[i]->setOpacity(255);
			}

			//住卡片做缩放动画
			auto scalebig = ScaleTo::create(0.2f, 1.1f);
			auto scalelittle = ScaleTo::create(0.2f, 0.9f);
			auto scalenormal = ScaleTo::create(0.2f, 1.0f);
			auto sequence = Sequence::create(scalebig, scalelittle, scalenormal, NULL);
			card->runAction(sequence);
		});


		auto flash_sequence = Sequence::create(spawan_flash, flash_down, NULL);
		littlecard_flash_sprite[i]->runAction(flash_sequence);

		this->addChild(littlecard_flash_sprite[i]);
		if (i < 3)
		{
			littlecard_flash_sprite[i]->setPosition(120, 580 - i * 100);
		}else{
			littlecard_flash_sprite[i]->setPosition(520, 580 -(i- 3) * 100);
		}
	}

	this->removeChild(progress_fr);
	//初始化ProgressTimer
	level_progress = ProgressTimer::create(Sprite::create("ui/exp1_1.png"));
	level_progress->setAnchorPoint(Vec2(0, 0.5));
	level_progress->setPercentage(0.0);
	level_progress->setBarChangeRate(Vec2(1, 0));
	level_progress->setType(ProgressTimer::Type::BAR);
	level_progress->setPosition(286, 340);
	level_progress->setMidpoint(Vec2(0 , 0));
	this->addChild(level_progress);  

	this->scheduleUpdate();   //调用计时器
}

void CardLevelUpLayer::update(float delta)
{
	float level_percentage = level_progress->getPercentage();
	level_percentage += 1;
	if (level_percentage <= 100)
	{
		level_progress->setPercentage(level_percentage);
	}else
	{
		this->unscheduleUpdate();
	}
}