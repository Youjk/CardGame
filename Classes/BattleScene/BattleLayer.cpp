#include "BattleLayer.h"


BattleLayer::BattleLayer(void)
{
	m_curSpeed = SPEED_X1;
	m_isShowGoAhead = false;
	m_curPlay = FIRST;

	m_pos_hero_x[0] = m_pos_hero_x[3] = 150;
	m_pos_hero_x[1] = m_pos_hero_x[4] = 320;
	m_pos_hero_x[2] = m_pos_hero_x[5] = 490;
	m_pos_hero_y[0] = m_pos_hero_y[1]= m_pos_hero_y[2] = 340;
	m_pos_hero_y[3] = m_pos_hero_y[4]= m_pos_hero_y[5] = 140;

	m_pos_monster_x[0] = m_pos_monster_x[3] = 150;
	m_pos_monster_x[1] = m_pos_monster_x[4] = 320;
	m_pos_monster_x[2] = m_pos_monster_x[5] = 490;
	m_pos_monster_y[0] = m_pos_monster_y[1] = m_pos_monster_y[2] = 820;
	m_pos_monster_y[3] = m_pos_monster_y[4] = m_pos_monster_y[5] = 620;

	m_pos_monster_x[6] = 320;
	m_pos_monster_y[6] = 720;
}


BattleLayer::~BattleLayer(void)
{
}

Scene* BattleLayer::createScene()
{
	Scene* scene = Scene::create();
	auto layer = BattleLayer::create();
	scene->addChild(layer);

	return scene;
}

bool BattleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	InitBk();
	InitContent();
	InitSkillAnimation();
	InitListener();
	this->schedule(schedule_selector(BattleLayer::first_play), 1.0f, 0, 0.1f);

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

//初始化背景及icon
void BattleLayer::InitBk()
{
	Size size = Director::getInstance()->getVisibleSize();

	//bk_1和bk_2循环滚动背景
	bk_1 = Sprite::create("ui/fightground_chengqiang.jpg");
	bk_1->setPosition(size.width/2, size.height/2);
	this->addChild(bk_1);

	bk_2 = Sprite::create("ui/fightground_chengqiang.jpg");
	bk_2->setPosition(size.width/2, size.height/2 * 3);
	this->addChild(bk_2);

	bk_3 = Sprite::create("ui/fightground_chengqiang_EndPos.png");
	bk_3->setPosition(size.width/2, size.height - bk_3->getContentSize().height/2);
	bk_1->addChild(bk_3);
	bk_3->setVisible(false);

	//左下角 X1
	for (int i = 0; i < 3; i++)
	{
		char speed_ptext[15];
		sprintf(speed_ptext, "speedx%d.png", i+1);
		speed[i] = Sprite::createWithSpriteFrameName(speed_ptext);
		speed[i]->setPosition(45, 40);
		this->addChild(speed[i]);
	}
	speed[1]->setVisible(false);
	speed[2]->setVisible(false);

	//左上角书icon
	Sprite* icon_fight_card = Sprite::createWithSpriteFrameName("icon_fight_card.png");
	icon_fight_card->setScale(0.7f);
	icon_fight_card->setPosition(40, size.height - 30);
	this->addChild(icon_fight_card);
	auto card_ttf = LabelTTF::create("1", "Arial", 20);
	card_ttf->setPosition(70, size.height - 30);
	card_ttf->setTag(500);
	this->addChild(card_ttf);

	//左上角八卦icon
	auto icon_fight_chip = Sprite::createWithSpriteFrameName("icon_fight_chip.png");
	icon_fight_chip->setScale(0.7f);
	icon_fight_chip->setPosition(140, size.height - 30);
	this->addChild(icon_fight_chip);
	auto chip_ttf = LabelTTF::create("1", "Arial", 20);
	chip_ttf->setPosition(170, size.height - 30);
	this->addChild(chip_ttf);

	//
	auto icon_fight_equipment = Sprite::createWithSpriteFrameName("icon_fight_equipment.png");
	icon_fight_equipment->setScale(0.7f);
	icon_fight_equipment->setPosition(240, size.height - 30);
	this->addChild(icon_fight_equipment);
	auto eqt_ttf = LabelTTF::create("1", "Arial", 20);
	eqt_ttf->setPosition(270, size.height - 30);
	this->addChild(eqt_ttf);

	//上边金币icon
	auto icon_fight_coin = Sprite::createWithSpriteFrameName("icon_fight_coin.png");
	icon_fight_coin->setScale(0.7f);
	icon_fight_coin->setPosition(240, size.height - 30);
	this->addChild(icon_fight_coin);
	auto coin_ttf = LabelTTF::create("1", "Arial", 20);
	coin_ttf->setPosition(270, size.height - 30);
	this->addChild(coin_ttf);

	//向上走的箭头
	gohead = Sprite::createWithSpriteFrameName("fight_goahead.png");
	gohead->setPosition(size.width /2, size.height/2 + 200);
	this->addChild(gohead, 1);
	gohead->setVisible(false);

}

//初始化卡片
void BattleLayer::InitContent()
{
	//添加自己的6张卡牌
	for (int i = 0; i < 6; i++)
	{
		hero[i] = Node::create();
		Sprite* card_frame = Sprite::createWithSpriteFrameName("bigcard_frame_class4_elite.png");
		hero[i]->addChild(card_frame);

		char pHeroName[20];
		sprintf(pHeroName, "bigcard_03%02d.png", 29 + i * 2);
		auto card_content = Sprite::createWithSpriteFrameName(pHeroName);
		hero[i]->addChild(card_content);

		auto card_occupation_base = Sprite::createWithSpriteFrameName("icon_occupation_base_elite.png");
		hero[i]->addChild(card_occupation_base);

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

		hero[i]->addChild(card_occupatuon);
		hero[i]->setScale(0.6f);
		hero[i]->setPosition(m_pos_hero_x[i], m_pos_hero_y[i]);
		this->addChild(hero[i]);
	}

	//敌人的card
	for (int i = 0; i < 6; i++)
	{
		monster[i] = Node::create();
		Sprite* card_frame = Sprite::createWithSpriteFrameName("bigcard_frame_class2.png");
		monster[i]->addChild(card_frame);

		auto card_content = Sprite::createWithSpriteFrameName("bigcard_0493.png");
		monster[i]->addChild(card_content);

		auto card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_mage_button.png");
		card_occupation->setScale(2.0f);
		card_occupation->setPosition(61, -73);
		monster[i]->addChild(card_occupation);
		monster[i]->setScale(0.7f);
		monster[i]->setPosition(m_pos_monster_x[i], m_pos_monster_y[i]);

		this->addChild(monster[i]);
	}

	//Boss
	monster[6] = Node::create();
	auto card_frame = Sprite::createWithSpriteFrameName("bigcard_frame_class3.png");
	monster[6]->addChild(card_frame);
	auto card_content = Sprite::createWithSpriteFrameName("bigcard_0489.png");
	monster[6]->addChild(card_content);

	auto card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_mage_button.png");
	card_occupation->setScale(2.0f);
	card_occupation->setPosition(61, -73);
	monster[6]->addChild(card_occupation);
	monster[6]->setScale(0.7f);
	monster[6]->setPosition(m_pos_monster_x[6], m_pos_monster_y[6]);
	monster[6]->setVisible(false);

	this->addChild(monster[6]);
}

void BattleLayer::InitSkillAnimation()
{
	auto thunde_skill = Animation::create();
	thunde_skill->setDelayPerUnit(0.1f);
	thunde_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("thunder_dian.png"));
	thunde_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("thunder_hua01.png"));
	thunde_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("thunder_hua02.png"));
	thunde_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("thunder_hua03.png"));
	thunde_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("thunder_hua04.png"));
	AnimationCache::getInstance()->addAnimation(thunde_skill, "thunde_skill");

	auto rock_skill = Animation::create();
	rock_skill->setDelayPerUnit(0.1f);
	rock_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("thunder_shandian.png"));
	rock_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("thunder_shisui01.png"));
	rock_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("thunder_shisui02.png"));
	rock_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("thunder_shisui03.png"));
	AnimationCache::getInstance()->addAnimation(rock_skill, "rock_skill");

	auto windhit_skill = Animation::create();
	windhit_skill->setDelayPerUnit(0.1f);
	windhit_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("windhit_01.png"));
	windhit_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("windhit_02.png"));
	windhit_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("windhit_03.png"));
	windhit_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("windhit_04.png"));
	windhit_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("windhit_05.png"));
	windhit_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("windhit_06.png"));
	AnimationCache::getInstance()->addAnimation(windhit_skill, "windhit_skill");

	auto zhongji_skill = Animation::create();
	zhongji_skill->setDelayPerUnit(0.1f);
	zhongji_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zhongji_shan0001.png"));
	zhongji_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zhongji_shan0005.png"));
	zhongji_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zhongji_shan0007.png"));
	AnimationCache::getInstance()->addAnimation(zhongji_skill, "zhongji_skill");

	auto tenarmy_skill = Animation::create();
	tenarmy_skill->setDelayPerUnit(0.1f);
	tenarmy_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tenarmy_01.png"));
	tenarmy_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tenarmy_03.png"));
	tenarmy_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tenarmy_05.png"));
	tenarmy_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tenarmy_07.png"));
	tenarmy_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tenarmy_09.png"));
	tenarmy_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tenarmy_11.png"));
	tenarmy_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tenarmy_13.png"));
	tenarmy_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tenarmy_15.png"));
	tenarmy_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tenarmy_19.png"));
	AnimationCache::getInstance()->addAnimation(tenarmy_skill, "tenarmy_skill");

	auto blizzard_skill = Animation::create();
	blizzard_skill->setDelayPerUnit(0.1f);
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0001.png"));
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0002.png"));
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0003.png"));
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0004.png"));
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0005.png"));
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0007.png"));
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0008.png"));
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0009.png"));
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0010.png"));
	blizzard_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blizzard_0011.png"));
	AnimationCache::getInstance()->addAnimation(blizzard_skill, "blizzard_skill");

	auto costomaAttack_skill = Animation::create();
	costomaAttack_skill->setDelayPerUnit(0.1f);
	costomaAttack_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("attack0002.png"));
	costomaAttack_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("attack0004.png"));
	costomaAttack_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("attack0005.png"));
	costomaAttack_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("attack0007.png"));
	costomaAttack_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("attack0009.png"));
	costomaAttack_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("attack0011.png"));
	AnimationCache::getInstance()->addAnimation(costomaAttack_skill, "costomaAttack_skill");

	auto heal_skill = Animation::create();
	heal_skill->setDelayPerUnit(0.1f);
	heal_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("heal_1.png"));
	heal_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("heal_2.png"));
	heal_skill->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("heal_3.png"));
	AnimationCache::getInstance()->addAnimation(heal_skill, "heal_skill");
}

void BattleLayer::initframe()
{

}

void BattleLayer::InitListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event){
		auto pt = touch->getLocation();

		if (pt.x < 100 && pt.y < 80)
		{
			switch (m_curSpeed)
			{
			case SPEED_X1:
				m_curSpeed = SPEED_X2;
				speed[0]->setVisible(false);
				speed[1]->setVisible(true);
				Director::getInstance()->getScheduler()->setTimeScale(2.0f); //时间加速
				break;
			case SPEED_X2:
				m_curSpeed = SPEED_X3;
				speed[1]->setVisible(false);
				speed[2]->setVisible(true);
				Director::getInstance()->getScheduler()->setTimeScale(3.0f);
				break;
			case SPEED_X3:
				m_curSpeed = SPEED_X1;
				speed[2]->setVisible(false);
				speed[0]->setVisible(true);
				Director::getInstance()->getScheduler()->setTimeScale(1.0f);
				break;
			default:
				break;
			}
		}
		else if (gohead->getBoundingBox().containsPoint(pt) && m_isShowGoAhead)
		{
			gohead->stopAllActions();
			gohead->setVisible(false);
			m_isShowGoAhead = false;
			if (m_curPlay == FIRST)
			{
				m_curPlay = SECOND;
				this->scheduleOnce(schedule_selector(BattleLayer::second_play), 0.2f);
			}else if(m_curPlay == SECOND)
			{
				m_curPlay = THIRD;
				bk_3->setVisible(true);
				this->scheduleOnce(schedule_selector(BattleLayer::third_play), 0.2f);
			}
		}
		return true;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event){

	};

	listener->onTouchEnded= [](Touch* touch, Event* event){

	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

//哪个位置英雄使用什么技能,攻击哪个敌人
void BattleLayer::show_hero_skill_normal(int pos, int type, int dst)
{
	if (type == 0)
	{
		hero[pos]->runAction(Sequence::create(RotateTo::create(0.1f, 5), 
			RotateTo::create(0.1f, -5), RotateTo::create(0.1f, 0) ,NULL));
		auto sword_left = Sprite::create("ui/hit0003.png");
		auto sword_right = Sprite::create("ui/hit0003.png");
		sword_left->setFlippedX(true);
		auto sword = Node::create();
		sword->addChild(sword_left);
		sword->addChild(sword_right);
		sword->setPosition(m_pos_hero_x[pos], m_pos_hero_y[pos]);
		this->addChild(sword);

		auto removeSword = CallFunc::create([=](){
			sword->removeFromParent();
		});
		sword->runAction(Sequence::create(FadeIn::create(0.2f),
			ScaleTo::create(0.1f, 1.1f),
			ScaleTo::create(0.1f, 0.9f),
			ScaleTo::create(0.1f, 1.0f),
			removeSword, NULL
			));
	}
	else if (type == 1)
	{
		hero[pos]->runAction(Sequence::create(RotateTo::create(0.1f, 5), 
			RotateTo::create(0.1f, -5), RotateTo::create(0.1f, 0) ,NULL));
		auto iceball = Sprite::create("ui/shoot.png");
		iceball->setPosition(m_pos_hero_x[pos], m_pos_hero_y[pos]);
		this->addChild(iceball);

		auto removeIceball = CallFunc::create([=](){
			iceball->removeFromParent();
		});
		iceball->runAction(Sequence::create(FadeIn::create(0.1f),
			MoveTo::create(0.2f, Vec2(m_pos_monster_x[dst], m_pos_monster_y[dst])),
			ScaleTo::create(0.1f, 1.1f),
			ScaleTo::create(0.1f, 0.9f),
			ScaleTo::create(0.1f, 1.0f),
			removeIceball,
			NULL
			));
	}
}

//哪个位置的英雄使用什么sprite用什么技能
void BattleLayer::show_hero_skill(int pos, const char* skill_name, const char* skill_spritename)
{
	hero[pos]->runAction(Sequence::create(
		RotateTo::create(0.1f, 5),
		RotateTo::create(0.1f, -5),
		RotateTo::create(0.1f, 0)
		,NULL));

	auto skill_animation = AnimationCache::getInstance()->getAnimation(skill_name);
	auto skill_sprite = Sprite::createWithSpriteFrameName(skill_spritename);
	skill_sprite->setPosition(m_pos_hero_x[pos], m_pos_hero_y[pos]);
	this->addChild(skill_sprite);

	auto remove = CallFunc::create([=](){
		skill_sprite->removeFromParent();
	});
	skill_sprite->runAction(Sequence::create(
		Animate::create(skill_animation),
		remove,
		NULL
		));
}

//显示怪物被打击效果
void BattleLayer::show_hit_skill(int pos, const char* skill_name, const char* skill_spritename)
{
	auto skill_animation = AnimationCache::getInstance()->getAnimation(skill_name);
	auto skill_sprite = Sprite::createWithSpriteFrameName(skill_spritename);
	skill_sprite->setPosition(m_pos_hero_x[pos], m_pos_hero_y[pos]);
	this->addChild(skill_sprite, 1);

	auto removeSprite = CallFunc::create([skill_sprite, pos, this](){
		skill_sprite->removeFromParent();
		monster[pos]->setVisible(false);
	});
	skill_sprite->runAction(Animate::create(skill_animation));
	skill_sprite->runAction(Sequence::create(
		Animate::create(skill_animation),
		removeSprite,
		NULL
		));
}

//显示被打击值
void BattleLayer::show_hit_value(int pos)
{
	int hit_value = (0.8 + CCRANDOM_0_1() * 0.4) * 30000;
	char hit_value_c[10];
	sprintf(hit_value_c, "%d", hit_value);
	LabelBMFont* sprite_value;
	int fnt_size = (0.8 + CCRANDOM_0_1()*0.6)*15;
	if (hit_value < 28000)
	{
		sprite_value = LabelBMFont::create(hit_value_c, "fonts/number_white.fnt", fnt_size);
	}else
	{
		sprite_value = LabelBMFont::create(hit_value_c, "fonts/number_red.fnt", fnt_size);
	}
	sprite_value->setPosition(m_pos_monster_x[pos], m_pos_monster_y[pos]);
	sprite_value->setOpacity(0);
	this->addChild(sprite_value);
	
	auto remove = CallFunc::create([=](){
		sprite_value->removeFromParent();
	});
	sprite_value->runAction(Sequence::create(
		FadeIn::create(0.5f),
		ScaleTo::create(0.2f, 1.3f),
		MoveBy::create(0.2f, Vec2(0, 10)),
		FadeOut::create(0.5f),
		remove,
		NULL
		));
}

//显示自己的血量
void BattleLayer::show_blood_value(int pos)
{
	int hit_value = (0.8 + CCRANDOM_0_1() * 0.4) * 10000;
	char hit_value_c[10];
	sprintf(hit_value_c, "%d", hit_value);
	LabelBMFont* sprite_value = LabelBMFont::create(hit_value_c, "fonts/number_green.fnt", 50);
	sprite_value->setPosition(m_pos_hero_x[pos], m_pos_hero_y[pos]);
	sprite_value->setOpacity(0);
	this->addChild(sprite_value);

	auto remove = CallFunc::create([=](){
		sprite_value->removeFromParent();
	});
	sprite_value->runAction(Sequence::create(
		FadeIn::create(0.5f),
		ScaleTo::create(0.2f, 1.3f),
		MoveBy::create(0.2f, Vec2(0, 10)),
		FadeOut::create(0.5f),
		remove,
		NULL
		));
}

//敌人死亡精灵
void BattleLayer::monster_die(int pos)
{
	auto monster_shock = Repeat::create(
		Sequence::create(
			RotateTo::create(0.1, -10),
			RotateTo::create(0.1, 10),
			RotateTo::create(0.1, 0),
			NULL
		), 2);

	auto remove = CallFunc::create([pos,this](){
		auto ghost = Sprite::create("ui/ghost.png");
		ghost->setPosition(m_pos_monster_x[pos], m_pos_monster_y[pos]);
		this->addChild(ghost);
		ghost->runAction(Spawn::create(MoveBy::create(0.3f, Vec2(0, 30)),ScaleTo::create(0.3f, 0.9f), NULL));

		auto removeghost = CallFunc::create([ghost](){
			ghost->removeFromParent();
		});

		ghost->runAction(Sequence::create(
			DelayTime::create(0.3f),
			FadeOut::create(0.3f),
			removeghost,
			NULL
			));
	});

	monster[pos]->runAction(Sequence::create(monster_shock, remove, NULL));
}

//在敌人上显示金币箱子
void BattleLayer::show_box(float dt)
{
	auto box = Node::create();
	auto box_bottom = Sprite::createWithSpriteFrameName("raffle_xiangqian1.png");
	auto box_top = Sprite::createWithSpriteFrameName("raffle_xiangai1.png");
	box->addChild(box_bottom, 3);
	box->addChild(box_top, 2);
	box_top->setPositionY(100);
	box_top->setTag(110);
	this->addChild(box);
	box->setScale(0.3f);
	box->setPosition(m_pos_monster_x[3], m_pos_monster_y[3]);

	auto change_boxtop = CallFunc::create([box, this](){
		box->removeChildByTag(110);
		auto box_top_new = Sprite::createWithSpriteFrameName("raffle_lanxianggai.png");
		box_top_new->setPosition(60, 90);
		
		auto box_middle = Sprite::createWithSpriteFrameName("raffle_xiangbei1.png");
		box_middle->setPositionY(30);
		box->addChild(box_middle,1);
		box->addChild(box_top_new, 2);

		auto card = Sprite::createWithSpriteFrameName("raffle_box_card.png");
		card->setScale(1.6f);
		card->setPositionY(150);
		box->addChild(card);

		auto removeBox = CallFunc::create([box, this](){
			box->removeAllChildren();
			box->removeFromParent();
			((LabelTTF*)(this->getChildByTag(500)))->setString("2");  //改变左上角值
		});
		card->runAction(Sequence::create(
			DelayTime::create(0.2f),
			Spawn::create(RotateTo::create(1.0f, 250), ScaleTo::create(1.0f, 0.2f), FadeOut::create(1.0f), NULL),
			removeBox,
			NULL
			));
	});

	box->runAction(Sequence::create(
		DelayTime::create(0.5f),
		change_boxtop,
		NULL
		));
}

void BattleLayer::showallmonster()
{
	if (m_curPlay == SECOND)
	{
		for (int i = 0; i < 6; i++)
		{
			monster[i]->setVisible(true);
		}
	}
	else if(m_curPlay == THIRD)
	{
		monster[0]->setVisible(true);
		monster[2]->setVisible(true);
		monster[3]->setVisible(true);
		monster[5]->setVisible(true);
		monster[6]->setVisible(true);
	}
}

//播放第一幕
void BattleLayer::first_play(float dt)
{
	this->scheduleOnce(schedule_selector(BattleLayer::showText), 0);
	this->schedule(schedule_selector(BattleLayer::first_play_0), 1.0f, 0, 1.5f);
	this->schedule(schedule_selector(BattleLayer::first_play_1), 1.0f, 0, 2.0f);
	this->schedule(schedule_selector(BattleLayer::first_play_2), 1.0f, 0, 2.5f);
	this->schedule(schedule_selector(BattleLayer::first_play_3), 1.0f, 0, 3.0f);
	this->schedule(schedule_selector(BattleLayer::first_play_4), 1.0f, 0, 3.5f);
	this->schedule(schedule_selector(BattleLayer::first_play_5), 1.0f, 0, 4.0f);
}

void BattleLayer::first_play_0(float dt)
{
	show_hero_skill_normal(0, 0, 0);
	show_hit_skill(3, "zhongji_skill", "zhongji_baojian.png");
	monster_die(3);
	show_hit_value(3);
}

void BattleLayer::first_play_1(float dt)
{
	show_hero_skill_normal(1, 1, 0);
	show_hero_skill_normal(1, 1, 5);
	show_hit_skill(0, "thunde_skill", "thunder_dian.png");
	monster_die(0);
	show_hit_value(0);
	show_hit_skill(5, "thunde_skill", "thunder_dian.png");
	monster_die(5);
	show_hit_value(5);
}

void BattleLayer::first_play_2(float dt)
{
	show_hero_skill(2, "costomaAttack_skill", "attack0002.png");
	show_hit_skill(4, "windhit_skill", "windhit_01.png");
	monster_die(4);
	show_hit_value(4);
}

void BattleLayer::first_play_3(float dt)
{
	show_hero_skill(3, "thunde_skill", "thunder_dian.png");
	show_hit_skill(2, "tenarmy_skill", "tenarmy_01.png");
	monster_die(2);
	show_hit_value(2);
}

void BattleLayer::first_play_4(float dt)
{
	show_hero_skill(4, "heal_skill","heal_1.png");
	show_blood_value(0);
	show_blood_value(1);
	show_blood_value(2);
}
void BattleLayer::first_play_5(float dt)
{
	show_hero_skill_normal(5, 1, 1);
	show_hit_skill(1,"blizzard_skill", "blizzard_0001.png");
	monster_die(1);
	show_hit_value(1);

	this->scheduleOnce(schedule_selector(BattleLayer::show_GoAhead), 1.0f);
}

void BattleLayer::show_GoAhead(float dt)
{
	if (!m_isShowGoAhead)
	{
		m_isShowGoAhead = true;
		gohead->setVisible(true);
		gohead->runAction(RepeatForever::create(Blink::create(1.0, 2)));
	}
}

void BattleLayer::runcardshake()
{
	for (int i = 0; i < 6; ++i)
	{
		auto shake = Sequence::create(MoveBy::create(0.4, Vec2(0,60)), MoveBy::create(0.1, Vec2(0, -60)), NULL);
		hero[i]->runAction(Repeat::create(shake, 4));
	}
}

void BattleLayer::runBk1(float dt)
{
	Size size = Director::getInstance()->getVisibleSize();
	bk_1->setPositionY(bk_1->getPositionY() - 8);
	bk_2->setPositionY(bk_1->getPositionY() + bk_1->getContentSize().height - 8);
	if (bk_2->getPositionY() == 480)
	{
		this->unschedule(schedule_selector(BattleLayer::runBk1));
		bk_1->setPositionY(size.height * 3 / 2);
		showallmonster();
	}
}

void BattleLayer::runBk2(float dt)
{
	bk_2->setPositionY(bk_2->getPositionY() - 8);
	bk_1->setPositionY(bk_2->getPositionY() + bk_2->getContentSize().height - 8);
	if (bk_1->getPositionY() == 480)
	{
		this->unschedule(schedule_selector(BattleLayer::runBk2));
		bk_2->setPositionY(Director::getInstance()->getVisibleSize().height * 3 / 2);
		showallmonster();
	}
}

void BattleLayer::second_play(float dt)
{
	this->schedule(schedule_selector(BattleLayer::runBk1));
	runcardshake();
	this->scheduleOnce(schedule_selector(BattleLayer::showText), 2.0);
	this->schedule(schedule_selector(BattleLayer::second_play_0), 1.0f, 0, 3.0f);
	this->schedule(schedule_selector(BattleLayer::second_play_1), 1.0f, 0, 3.5f);
	this->schedule(schedule_selector(BattleLayer::second_play_2), 1.0f, 0, 4.0f);
	this->schedule(schedule_selector(BattleLayer::second_play_3), 1.0f, 0, 4.5f);
	this->schedule(schedule_selector(BattleLayer::second_play_4), 1.0f, 0, 5.0f);
	this->schedule(schedule_selector(BattleLayer::second_play_5), 1.0f, 0, 5.5f);
}

void BattleLayer::second_play_0(float dt)
{
	show_hero_skill_normal(0, 0, 0);
	show_hit_skill(3, "zhongji_skill", "zhongji_baojian.png");
	monster_die(3);
	show_hit_value(3);
}

void BattleLayer::second_play_1(float dt)
{
	show_hero_skill_normal(1, 1, 0);
	show_hero_skill_normal(1, 1, 5);
	show_hit_skill(0, "thunde_skill", "thunder_dian.png");
	monster_die(0);
	show_hit_value(0);
	show_hit_skill(5, "thunde_skill", "thunder_dian.png");
	monster_die(5);
	show_hit_value(5);
}

void BattleLayer::second_play_2(float dt)
{
	show_hero_skill(2, "costomaAttack_skill", "attack0002.png");
	show_hit_skill(4, "windhit_skill", "windhit_01.png");
	monster_die(4);
	show_hit_value(4);
}

void BattleLayer::second_play_3(float dt)
{
	show_hero_skill(3, "thunde_skill", "thunder_dian.png");
	show_hit_skill(2, "tenarmy_skill", "tenarmy_01.png");
	monster_die(2);
	show_hit_value(2);
}

void BattleLayer::second_play_4(float dt)
{
	show_hero_skill(4, "heal_skill","heal_1.png");
	show_blood_value(0);
	show_blood_value(1);
	show_blood_value(2);
}

void BattleLayer::second_play_5(float dt)
{
	show_hero_skill_normal(5, 1, 1);
	show_hit_skill(1,"blizzard_skill", "blizzard_0001.png");
	monster_die(1);
	show_hit_value(1);

	this->scheduleOnce(schedule_selector(BattleLayer::show_GoAhead), 1.0f);
}

void BattleLayer::third_play(float dt)
{
	this->schedule(schedule_selector(BattleLayer::runBk2));
	runcardshake();
	this->scheduleOnce(schedule_selector(BattleLayer::showText), 2.0);
	this->schedule(schedule_selector(BattleLayer::third_play_0), 1.0f, 0, 3.0f);
	this->schedule(schedule_selector(BattleLayer::third_play_1), 1.0f, 0, 3.5f);
	this->schedule(schedule_selector(BattleLayer::third_play_2), 1.0f, 0, 4.0f);
	this->schedule(schedule_selector(BattleLayer::third_play_3), 1.0f, 0, 4.5f);
	this->schedule(schedule_selector(BattleLayer::third_play_4), 1.0f, 0, 5.0f);
	this->schedule(schedule_selector(BattleLayer::third_play_5), 1.0f, 0, 5.5f);
}

void BattleLayer::third_play_0(float dt)
{
	show_hero_skill_normal(0, 0, 0);
	show_hit_skill(0, "zhongji_skill", "zhongji_baojian.png");
	monster_die(0);
	show_hit_value(0);
	show_hit_value(0);
}

void BattleLayer::third_play_1(float dt)
{
	show_hero_skill_normal(1, 1, 2);
	show_hero_skill_normal(1, 1, 3);
	show_hit_skill(2, "thunde_skill", "thunder_dian.png");
	monster_die(2);
	show_hit_value(2);
	show_hit_skill(3, "thunde_skill", "thunder_dian.png");
	monster_die(5);
	show_hit_value(5);
}

void BattleLayer::third_play_2(float dt)
{
	show_hero_skill(2, "costomaAttack_skill", "attack0002.png");
	show_hit_skill(5, "windhit_skill", "windhit_01.png");
	monster_die(5);
	show_hit_value(5);
}

void BattleLayer::third_play_3(float dt)
{
	show_hero_skill(2, "costomaAttack_skill", "attack0002.png");
	show_hit_skill(5, "windhit_skill", "windhit_01.png");
	monster_die(5);
	show_hit_value(5);
}

void BattleLayer::third_play_4(float dt)
{
	show_hero_skill(4, "heal_skill", "heal_1.png");
	show_blood_value(0);
	show_blood_value(3);
	show_blood_value(5);
}

void BattleLayer::third_play_5(float dt)
{
	this->scheduleOnce(schedule_selector(BattleLayer::showVictory), 1.0f);
}


void BattleLayer::showVictory(float dt)
{
	victory = Node::create();
	this->addChild(victory);
	victory->setPosition(320, 700);

	auto victory_flash = Sprite::create("ui/victory_flash.png");
	victory->addChild(victory_flash);
	victory_flash->runAction(RepeatForever::create(RotateBy::create(0.5, 90)));

	auto victory_weapon1 = Sprite::createWithSpriteFrameName("victory_weapon1.png");
	victory->addChild(victory_weapon1);
	victory_weapon1->setPosition(-50, 100);

	auto victory_weapon2 = Sprite::createWithSpriteFrameName("victory_weapon1.png");
	victory->addChild(victory_weapon2);
	victory_weapon2->setPosition(50, 100);

	auto victory_drum = Sprite::createWithSpriteFrameName("victory_drum.png");
	victory->addChild(victory_drum);
	victory_drum->setOpacity(0);
	victory_drum->setScale(0.2f);
	victory_drum->runAction(Spawn::create(ScaleTo::create(0.2f, 1.0f), FadeIn::create(0.2f), NULL));

	auto victory_word = Sprite::createWithSpriteFrameName("victory_word.png");
	victory->addChild(victory_word);
	victory_word->setOpacity(0);
	victory_word->setScale(0.2f);
	victory_word->runAction(Spawn::create(ScaleTo::create(0.2f, 1.0f), FadeIn::create(0.2f), NULL));

	this->schedule(schedule_selector(BattleLayer::showResult), 3.0f);
	
}

void BattleLayer::showText(float dt)
{
	if (m_curPlay == FIRST)
	{
		auto zhan = Sprite::createWithSpriteFrameName("fightstar_word_fight1.png");
		zhan->setPosition(270, 480);
		zhan->setOpacity(0);
		this->addChild(zhan);

		auto dou = Sprite::createWithSpriteFrameName("fightstar_word_fight2.png");
		dou->setOpacity(0);
		dou->setPosition(370, 480);
		this->addChild(dou);

		zhan->runAction(Sequence::create(
			FadeIn::create(0.3f),
			ScaleTo::create(0.1f, 1.1f),
			ScaleTo::create(0.1f, 0.9f),
			ScaleTo::create(.01f, 1.0f),
			DelayTime::create(0.3f),
			FadeOut::create(0.3f),
			NULL));
		dou->runAction(Sequence::create(
			FadeIn::create(0.3f),
			ScaleTo::create(0.1f, 1.1f),
			ScaleTo::create(0.1f, 0.9f),
			ScaleTo::create(.01f, 1.0f),
			DelayTime::create(0.3f),
			FadeOut::create(0.3f),
			NULL));
	}else if(m_curPlay == SECOND)
	{

	}else if (m_curPlay == THIRD)
	{
		auto boss_text = Sprite::createWithSpriteFrameName("fightstar_word_boss.png");
		boss_text->setPosition(350, 480);
		this->addChild(boss_text);
		boss_text->setOpacity(0);
		boss_text->runAction(Spawn::create(
			MoveBy::create(0.5f, Vec2(60, 0)),
			Sequence::create(FadeIn::create(0.25f), FadeOut::create(0.25f), NULL),
			NULL));
	}
}

void BattleLayer::showResult(float dt)
{
	Director::getInstance()->getScheduler()->setTimeScale(1.0f);
	NotificationCenter::getInstance()->postNotification("showBattleResult");
	Director::getInstance()->popScene();
}