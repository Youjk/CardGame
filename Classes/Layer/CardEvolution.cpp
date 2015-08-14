#include "CardEvolution.h"
#include "Utils/AppStringFile.h"


CardEvolution::CardEvolution(void)
{
}


CardEvolution::~CardEvolution(void)
{
}

bool CardEvolution::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initframe();
	initcontent();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event){

		Rect before_hero_rect = Rect(92, 332, 163, 96);
		if (before_hero_rect.containsPoint(touch->getLocationInView()))
		{
			if (kuang == NULL)
			{
				kuang = Sprite::createWithSpriteFrameName("evolution_kuang.png");
				kuang->setScaleX(1.5f);
				kuang->setScaleY(1.55f);
				kuang->setPosition(130, 197);
				cardevolutionbase->addChild(kuang);
			}
			return true;
		}else
		{
			return false;
		}
	};

	listener->onTouchEnded = [this](Touch* touch, Event* event){
		if (kuang)
		{
			cardevolutionbase->removeChild(kuang, true);
			kuang = NULL;
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


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

void CardEvolution::initframe()
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

	//进化背景
	auto listbase = Sprite::create("ui/cardevolvebase.jpg");  
	listbase->setScale(1.4f);
	listbase->setPosition(size.width/2, 410);
	this->addChild(listbase);

	//顶部文字的背景
	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);

	//顶部的文字
	auto titletext = Sprite::createWithSpriteFrameName("titlename_cardevolve.png");
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

	//两个英雄进化框的背景
	cardevolutionbase = Sprite::create("ui/cardevolvebase_02_16_9.png");
	cardevolutionbase->setPosition(size.width/2, 475);
	cardevolutionbase->setScale(1.2f);
	this->addChild(cardevolutionbase);

	//5个装备的背景
	for (int i = 0; i < 5; ++i)
	{
		equit_bk[i] = Sprite::createWithSpriteFrameName("littlecard_empty.png");
		equit_bk[i]->setScale(0.8f);
		equit_bk[i]->setPosition(130 + i * 95, 253);
		this->addChild(equit_bk[i]);
	}

	//进化按钮
	auto startevolve_normal = Sprite::createWithSpriteFrameName("button_left_0.png");
	auto startevolve_pressed = Sprite::createWithSpriteFrameName("button_left_1.png");
	auto startevolve_disable = Sprite::createWithSpriteFrameName("button_left_2.png");
	startevolve_Item = MenuItemSprite::create(startevolve_normal, startevolve_pressed, startevolve_disable);
	startevolve_Item->setCallback(CC_CALLBACK_1(CardEvolution::start_evolve_menucallback, this));

	auto text_startevolve = Sprite::createWithSpriteFrameName("text_starevolve.png");
	text_startevolve->setPosition(startevolve_normal->getContentSize().width/2, startevolve_normal->getContentSize().height/2);
	startevolve_Item->addChild(text_startevolve);

	auto menu_startevolve = Menu::create(startevolve_Item, NULL);
	menu_startevolve->setPosition(size.width/2, 183);
	this->addChild(menu_startevolve);
}

void CardEvolution::initcontent()
{
	//选择英雄前
	choose_card_before = Node::create();
	choose_card_before->setPosition(130, 190);
	choose_card_before->setScale(0.85f);
	cardevolutionbase->addChild(choose_card_before);

	Sprite* frame_before = Sprite::createWithSpriteFrameName("bigcard_frame_class2_elite.png");
	choose_card_before->addChild(frame_before);
	card_before = Sprite::createWithSpriteFrameName("bigcard_0001.png");
	choose_card_before->addChild(card_before);

	auto occupation_before = Sprite::createWithSpriteFrameName("icon_occupation_base2.png");
	occupation_before->setScale(1.3f);
	occupation_before->setPosition(13, -15);
	choose_card_before->addChild(occupation_before);
	auto occupation_warrior_before = Sprite::createWithSpriteFrameName("icon_occupation_warrior_button.png");
	occupation_warrior_before->setScale(1.6f);
	occupation_warrior_before->setPosition(63, -78);
	choose_card_before->addChild(occupation_warrior_before);

	Sprite* star_before[3];
	for (int i = 0; i < 3; i++)
	{
		star_before[i] = Sprite::createWithSpriteFrameName("star_5.png");
		star_before[i]->setScale(0.85f);
		star_before[i]->setPosition(-115, 33 + i * 31);
		choose_card_before->addChild(star_before[i]);
	}

	//选择英雄后
	Node* choose_card_after = Node::create();
	choose_card_after->setPosition(370, 190);
	choose_card_after->setScale(0.85f);
	cardevolutionbase->addChild(choose_card_after);

	Sprite* frame_after = Sprite::createWithSpriteFrameName("bigcard_frame_class2_elite.png");
	choose_card_after->addChild(frame_after);
	auto card_after = Sprite::createWithSpriteFrameName("bigcard_0002.png");
	choose_card_after->addChild(card_after);

	auto occupation_after = Sprite::createWithSpriteFrameName("icon_occupation_base3.png");
	occupation_after->setScale(1.3f);
	occupation_after->setPosition(13, -15);
	choose_card_after->addChild(occupation_after);

	auto occupation_warrior_after = Sprite::createWithSpriteFrameName("icon_occupation_warrior_button.png");
	occupation_warrior_after->setScale(1.6f);
	occupation_warrior_after->setPosition(63, -78);
	choose_card_after->addChild(occupation_warrior_after);

	Sprite* star_after[4];
	for (int i = 0; i < 4; i++)
	{
		star_after[i] = Sprite::createWithSpriteFrameName("star_5.png");
		star_after[i]->setScale(0.85f);
		star_after[i]->setPosition(115, 2 + i * 31);
		choose_card_after->addChild(star_after[i]);
	}

	//遮罩
	shadow = LayerColor::create(Color4B(30, 30, 30, 150));
	shadow->setContentSize(Size(160, 195));
	shadow->setPosition(290, 100);
	cardevolutionbase->addChild(shadow);

	//武器
	for (int i = 0; i < 5; ++i)
	{
		weapon_evolve[i] = Node::create();

		char name[30];
		sprintf(name, "icon_equipment2_1_%d.png", i + 1);
		auto weapon_evolve_pic = Sprite::createWithSpriteFrameName(name);
		weapon_evolve[i]->addChild(weapon_evolve_pic);

		auto weapon_evolve_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class3.png");
		weapon_evolve[i]->addChild(weapon_evolve_frame);

		sprintf(name, "weapon0%d_evolve", i + 1);
		auto weapon_evolve_text = LabelTTF::create(AppStringFile::getInstance()->getStringForKey(name), "Arial", 20);
		weapon_evolve_text->setColor(Color3B(0, 230, 0));
		weapon_evolve_text->setPosition(25, -30);
		weapon_evolve[i]->addChild(weapon_evolve_text);
		weapon_evolve[i]->setPosition(48, 48);
		equit_bk[i]->addChild(weapon_evolve[i]);
	}

	//英雄属性文本
	std::string textname_before[4] = {"text_level_evolve_before", "text_life_evolve_before",
							"text_attack_evolve_before","text_skill_evolve_before"};
	std::string name_before[4] = {"level_evolve_before", "life_evolve_before",
					"attack_evolve_before","skill_evolve_before"};
	std::string textname_after[4] = {"text_level_evolve_after", "text_life_evolve_after",
		"text_attack_evolve_after","text_skill_evolve_after"};
	std::string name_after[4] = {"level_evolve_after_02", "life_evolve_after",
		"attack_evolve_after","skill_evolve_after"};
	for (int i = 0; i < 4; ++i)
	{
		//左边
		text_evolve_before[i] = LabelTTF::create(AppStringFile::getInstance()->getStringForKey(textname_before[i]), "Arial", 18);
		text_evolve_before[i]->setPosition(75, 88 - i * 23);
		cardevolutionbase->addChild(text_evolve_before[i]);

		value_evolve_before[i] = LabelTTF::create(AppStringFile::getInstance()->getStringForKey(name_before[i]), "Arial", 18);
		value_evolve_before[i]->setColor(Color3B(0, 230, 0));
		value_evolve_before[i]->setAnchorPoint(Vec2(1.0, 0.5));
		value_evolve_before[i]->setPosition(205, 88 - i * 23);
		cardevolutionbase->addChild(value_evolve_before[i]);

		//右边
		auto text_after = LabelTTF::create(AppStringFile::getInstance()->getStringForKey(textname_after[i]), "Arial", 18);
		text_after->setAnchorPoint(Vec2(0, 0.5));
		text_after->setPosition(300, 88 - i * 23);
		cardevolutionbase->addChild(text_after);

		auto value_after = LabelTTF::create(AppStringFile::getInstance()->getStringForKey(name_after[i]), "Arial", 18);
		value_after->setColor(Color3B(0, 230, 0));
		value_after->setAnchorPoint(Vec2(1.0, 0.5));
		value_after->setPosition(445, 88 - i * 23);
		cardevolutionbase->addChild(value_after);
	}
	auto value_after = LabelTTF::create(AppStringFile::getInstance()->getStringForKey("level_evolve_after_01"), "Arial", 18);
	value_after->setAnchorPoint(Vec2(1.0, 0.5));
	value_after->setPosition(425, 88);
	cardevolutionbase->addChild(value_after);
}

//进化按钮回调
void  CardEvolution::start_evolve_menucallback(Ref* pSender)
{
	//光帧动画
	startevolve_Item->setEnabled(false);

	//动画
	auto weapon_evolve_animation = Animation::create();
	weapon_evolve_animation->setDelayPerUnit(0.1f);
	weapon_evolve_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("evolution_guang04.png"));
	weapon_evolve_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("evolution_guang02.png"));
	weapon_evolve_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("evolution_guang01.png"));
	AnimationCache::getInstance()->addAnimation(weapon_evolve_animation, "wepon_evolve_animation");

	//装备动画
	for (int i = 0; i < 5; i++)
	{
		weapon_evolve_animate_sprite[i] = Sprite::createWithSpriteFrameName("evolution_guang04.png");
		weapon_evolve_animate_sprite[i]->setPosition(130 + i * 95, 253);
		this->addChild(weapon_evolve_animate_sprite[i]);

		auto weapon_evolve_animate = Animate::create(weapon_evolve_animation);
		auto weapon_evolve_disappear = CallFunc::create([i,this](){
			weapon_evolve_animate_sprite[i]->removeFromParent();
			weapon_evolve[i]->removeFromParent();
		});
		Sequence* sequence;
		if (i == 4)
		{
			auto before_card_dissappear = CallFunc::create(CC_CALLBACK_0(CardEvolution::before_card_sprite_disappear, this));
			sequence = Sequence::create(weapon_evolve_animate, weapon_evolve_disappear, before_card_dissappear, NULL);
		}else
		{
			sequence = Sequence::create(weapon_evolve_animate, weapon_evolve_disappear, NULL);
		}
		weapon_evolve_animate_sprite[i]->runAction(sequence);
	}
}

//卡牌动画
void CardEvolution::before_card_sprite_disappear()
{
	const int littlecard_count = 9;
	
	auto littlecard_animation = Animation::create();
	littlecard_animation->setDelayPerUnit(0.1f);
	littlecard_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("evolution_quan.png"));
	littlecard_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("evolution_pai.png"));

	int posX[littlecard_count] = {110, 180, 250, 110, 150, 250, 110, 180, 250};
	int posY[littlecard_count] = {450, 450, 420, 530, 530, 530, 610, 610, 610};

	//石头动画
	for (int i = 0; i < littlecard_count; i++)
	{
		auto littlecard = Sprite::createWithSpriteFrameName("evolution_bbb.png");
		littlecard->setRotation(36 * i);
		littlecard->setScale(0.6f);
		littlecard->setPosition(posX[i], posY[i]);

		//动作
		auto littlecard_animate = Animate::create(littlecard_animation);
		auto littlecard_moveto = MoveTo::create(0.3f, Vec2(190, 530));
		auto littlecard_disappear = CallFunc::create([=](){
			littlecard->removeFromParent();
		});
		auto littlecard_sequence = Sequence::create(littlecard_animate, littlecard_moveto, littlecard_disappear, NULL);
		littlecard->runAction(littlecard_sequence);
		this->addChild(littlecard);
	}

	//光动画
	before_card_animate_sprite = Sprite::createWithSpriteFrameName("evolution_guang04.png");
	before_card_animate_sprite->setPosition(170, 530);
	this->addChild(before_card_animate_sprite);

	auto before_card_sprite_delay = DelayTime::create(0.3f);
	auto before_card_sprite_animate = Animate::create(AnimationCache::getInstance()->getAnimation("wepon_evolve_animation"));
	auto before_card_sprite_disappear = CallFunc::create([this](){
		before_card_animate_sprite->removeFromParent();
	});
	auto  before_card_sprite_sequence = Sequence::create(before_card_sprite_delay, before_card_sprite_animate, before_card_sprite_disappear, NULL);
	before_card_animate_sprite->runAction(before_card_sprite_sequence);

	//卡片消失
	auto before_card_fadeout = FadeOut::create(0.5f);
	auto before_card_dis = CallFunc::create([this](){
		choose_card_before->removeFromParent();
		for (int i = 0; i < 4; i++)
		{
			value_evolve_before[i]->removeFromParent();
		}
		after_card_show();
	});
	choose_card_before->runAction(Sequence::create(before_card_fadeout,before_card_dis, NULL));
}

//白色卡片淡入淡出动画
void CardEvolution::after_card_show()
{
	shan = Sprite::createWithSpriteFrameName("evolution_shan.png");
	shan->setScaleX(1.5f);
	shan->setScaleY(1.55f);
	shan->setPosition(370, 200);
	cardevolutionbase->addChild(shan);
	shan->setOpacity(0);

	auto shan_fadein = FadeIn::create(0.3f);
	auto shan_fadeout = FadeOut::create(0.3f);
	auto shan_disappear = CallFunc::create([this](){
		shan->removeFromParent();
		cardevolutionbase->removeChild(shadow, true);
		show_choose_hero();
	});

	shan->runAction(Sequence::create(shan_fadein, shan_fadeout, shan_disappear, NULL));
}

//选择英雄字体
void CardEvolution::show_choose_hero()
{
	auto eatcard_choosecard = Sprite::createWithSpriteFrameName("eatcard_choosecard.png");
	eatcard_choosecard->setScale(0.8f);
	eatcard_choosecard->setPosition(130, 200);
	cardevolutionbase->addChild(eatcard_choosecard);

	auto choose_card_bink = Blink::create(1.5f,2);
	eatcard_choosecard->runAction(RepeatForever::create(choose_card_bink));
}