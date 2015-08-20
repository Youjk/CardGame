#include "RaffleTenLayer.h"


RaffleTenLayer::RaffleTenLayer(void)
{
	m_cardth = 0;
	m_pos_x[0] = m_pos_x[9] = 100;
	m_pos_x[1] = m_pos_x[8] = 210;
	m_pos_x[2] = m_pos_x[7] = 320;
	m_pos_x[3] = m_pos_x[6] = 430;
	m_pos_x[4] = m_pos_x[5] = 540;
	m_pos_y[0] = m_pos_y[1] = m_pos_y[2] = m_pos_y[3] = m_pos_y[4] = 850;
	m_pos_y[5] = m_pos_y[6] = m_pos_y[7] = m_pos_y[8] = m_pos_y[9] = 710;
}


RaffleTenLayer::~RaffleTenLayer(void)
{
}

Scene* RaffleTenLayer::createScene()
{
	Scene* scene = Scene::create();
	auto layer = RaffleTenLayer::create();
	scene->addChild(layer);

	return scene;
}

bool RaffleTenLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initBK();
	return true;
}

void RaffleTenLayer::initBK()
{
	Size size = Director::getInstance()->getVisibleSize();

	//背景图片
	auto bk = Sprite::create("ui/backgroud_raffleanimation.jpg");
	bk->setScale(2.0f);
	bk->setPosition(size.width/2, size.height/2);
	this->addChild(bk);

	raffle_daguang_flash = Sprite::createWithSpriteFrameName("raffle_daguang00.png");
	raffle_daguang_flash->setScale(2.5f);
	raffle_daguang_flash->setPosition(size.width/2, 290);
	this->addChild(raffle_daguang_flash);

	//动画
	auto raffle_daguang_blink = Blink::create(4.0f, 3);
	raffle_daguang_flash->runAction(raffle_daguang_blink);

	//中间地下那搓圆盘光
	raffle_guang = Sprite::createWithSpriteFrameName("raffle_guang00.png");
	raffle_guang->setScale(0.2f);
	raffle_guang->setPosition(size.width/2, 310);
	this->addChild(raffle_guang);
	auto raffle_guang_seq = Sequence::create(ScaleTo::create(0.3f, 1.2f),
		CallFunc::create(CC_CALLBACK_0(RaffleTenLayer::show_chuizhi_guang,this)),
		NULL);
	raffle_guang->runAction(raffle_guang_seq);
}

void RaffleTenLayer::show_chuizhi_guang()
{
	chuizhiguang = Node::create();

	ProgressTimer* guangwai = ProgressTimer::create(Sprite::createWithSpriteFrameName("raffle_guangwai00.png"));
	guangwai->setType(ProgressTimer::Type::BAR);
	chuizhiguang->addChild(guangwai);
	guangwai->setMidpoint(Vec2(0, 0));
	guangwai->setBarChangeRate(Vec2(0, 1));
	guangwai->runAction(ProgressTo::create(0.3f, 100));
	this->addChild(chuizhiguang);
	chuizhiguang->setPosition(320, 380);

	auto remove = CallFunc::create([this](){
		this->removeChild(chuizhiguang);
		this->removeChild(raffle_guang);

		//中间白色八卦
		raffle_he_flash = Sprite::createWithSpriteFrameName("raffle_he00.png");
		raffle_he_flash->setPosition(320, 330);
		this->addChild(raffle_he_flash);

		auto raffle_he_seq = Sequence::create(ScaleTo::create(0.5f, 2.0),
			ScaleTo::create(0.5f, 1.0f),
			ScaleTo::create(0.5f, 2.0f),
			ScaleTo::create(0.5f, 1.0f),
			ScaleTo::create(0.5f, 2.0f),
			ScaleTo::create(0.5f, 1.0f),
			NULL);

		raffle_he_flash->runAction(raffle_he_seq);

		bai_xiangzi = Sprite::createWithSpriteFrameName("raffle_bai100.png");
		bai_xiangzi->setScale(2.0f);
		bai_xiangzi->setPosition(320, 380);
		bai_xiangzi->setOpacity(0);

		auto bai_xiangzi_seq = Sequence::create(FadeIn::create(0.5f),
			CallFunc::create(CC_CALLBACK_0(RaffleTenLayer::show_xiangzi, this)),
			NULL);
		bai_xiangzi->runAction(bai_xiangzi_seq);
		this->addChild(bai_xiangzi);
	});
	auto seq = Sequence::create(DelayTime::create(0.3f), remove, NULL);
	chuizhiguang->runAction(seq);
}

void RaffleTenLayer::show_xiangzi()
{
	this->removeChild(raffle_he_flash);
	this->removeChild(bai_xiangzi);

	//白色光
	raffle_guangbai = Sprite::createWithSpriteFrameName("raffle_guangbai00.png");
	raffle_guangbai->setPosition(320, 380);
	raffle_guangbai->setOpacity(0);
	this->addChild(raffle_guangbai);

	auto guangbai_fadein = FadeIn::create(1.0f);
	auto guangbai_scale = ScaleTo::create(1.0f, 10.0f);
	auto guang_bai_spw = Spawn::create(guangbai_fadein, guangbai_scale, NULL);
	raffle_guangbai->runAction(guang_bai_spw);

	auto remove = CallFunc::create([this](){
		this->removeChild(raffle_guangbai);
		this->removeChild(xiangzi_top);

		xiangzi_top_new = Sprite::createWithSpriteFrameName("raffle_xianggai.png");
		xiangzi_top_new->setPosition(380, 430);
		this->addChild(xiangzi_top_new);

		auto xiangzi_xiangbei = Sprite::createWithSpriteFrameName("raffle_xiangbei.png");
		xiangzi_xiangbei->setPosition(320, 370);
		this->addChild(xiangzi_xiangbei);

		auto card_guang = Sprite::createWithSpriteFrameName("raffle_guangbai00.png");
		card_guang->setPosition(320, 400);
		card_guang->setScale(2.0f);
		card_guang->setOpacity(0);
		this->addChild(card_guang);

		auto card_guang_rotate = RotateBy::create(0.5f, 90);
		auto card_guang_rp = RepeatForever::create(card_guang_rotate);
		card_guang->runAction(card_guang_rp);

		auto card_guang_fadein = FadeIn::create(2.0f);
		card_guang->runAction(card_guang_fadein);

		auto show_card_seq = Sequence::create(DelayTime::create(0.3f), CallFunc::create(CC_CALLBACK_0(RaffleTenLayer::show_card,this)), NULL);
		this->runAction(show_card_seq);
	});

	auto guangbai_seq = Sequence::create(DelayTime::create(1.0f),
		remove,
		NULL);
	raffle_guangbai->runAction(guangbai_seq);

	xiangzi_bottom = Sprite::createWithSpriteFrameName("raffle_xiangqian2.png");
	xiangzi_bottom->setOpacity(0);
	xiangzi_bottom->setPosition(320, 340);
	this->addChild(xiangzi_bottom);
	auto buttom_fadein = FadeIn::create(0.5f);
	xiangzi_bottom->runAction(buttom_fadein);

	//箱子盖
	xiangzi_top = Sprite::createWithSpriteFrameName("raffle_xianggai2.png");
	xiangzi_top->setOpacity(0);
	xiangzi_top->setPosition(320, 440);
	this->addChild(xiangzi_top);
	auto top_fadein = FadeIn::create(0.5f);
	auto top_seq = Sequence::create(top_fadein,
		MoveBy::create(0.3f, Vec2(0, 30)),
		NULL);
	xiangzi_top->runAction(top_seq);
}

void RaffleTenLayer::show_card()
{
	this->schedule(schedule_selector(RaffleTenLayer::show_box_card), 0.2f);
}

void RaffleTenLayer::show_box_card(float dt)
{
	if (m_cardth < 10)
	{
		auto box_card = Sprite::createWithSpriteFrameName("raffle_box_card.png");
		box_card->setScale(0.3f);
		box_card->setTag(m_cardth);
		box_card->setPosition(320, 400);
		this->addChild(box_card);

		auto box_card_moveto = MoveTo::create(0.2f, Vec2(m_pos_x[m_cardth], m_pos_y[m_cardth]));
		auto box_card_scale = ScaleTo::create(0.2f, 1.0f);
		box_card->runAction(Spawn::create(box_card_moveto, box_card_scale, NULL));

		m_cardth++;
	}else
	{
		this->unschedule(schedule_selector(RaffleTenLayer::show_box_card));
		this->schedule(schedule_selector(RaffleTenLayer::show_box_card_front), 0.2f);
		m_cardth = 0;
	}
}

//翻牌
void RaffleTenLayer::show_box_card_front(float dt)
{
	if (m_cardth < 10)
	{
		auto remove_box_card = CallFunc::create([this](){
			//this->removeChild(this->getChildByTag(m_cardth));
		});
		this->getChildByTag(m_cardth)->runAction(Sequence::create(
				FadeOut::create(0.3f),
				remove_box_card,
				NULL));

		auto card = Node::create();
		auto card_frame = Sprite::createWithSpriteFrameName("bigcard_frame_class4_elite.png");
		card->addChild(card_frame);

		card_frame->setOpacity(0);
		auto card_frame_fadein = FadeIn::create(0.5f);
		card_frame->runAction(card_frame_fadein);

		char pHeroName[20];
		sprintf(pHeroName, "bigcard_03%02d.png", 29 + m_cardth * 2);
		auto card_content = Sprite::createWithSpriteFrameName(pHeroName);
		card->addChild(card_content);
		card_content->setOpacity(0);
		auto card_content_fadein = FadeIn::create(0.5f);
		card_content->runAction(card_content_fadein);

		auto card_occupation_base = Sprite::createWithSpriteFrameName("icon_occupation_base_elite.png");
		card->addChild(card_occupation_base);
		card_occupation_base->setOpacity(0);
		auto card_occupation_fade = FadeIn::create(0.5f);
		card_occupation_base->runAction(card_occupation_fade);

		Sprite* card_occupation;

		switch (m_cardth)
		{
		case 0:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_warrior_button.png");
			break;
		case 1:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_druid_button.png");
			break;
		case 2:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_mage_button.png");
			break;
		case 3:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_priest_button.png");
			break;
		case 4:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_warlock_button.png");
			break;
		case 5:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_hunter_button.png");
			break;
		case 6:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_shaman_button.png");
			break;
		case 7:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_rogue_button.png");
			break;
		case 8:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_druid_button.png");
			break;
		case 9:
			card_occupation = Sprite::createWithSpriteFrameName("icon_occupation_paladin_button.png");
			break;
		default:
			break;
		}

		card_occupation->setScale(2.0f);
		card_occupation->setPosition(61, -73);
		card->addChild(card_occupation);
		card_occupation->setOpacity(0);

		auto card_occupation_fadein = FadeIn::create(0.5f);
		card->setScale(0.5f);
		card->setPosition(m_pos_x[m_cardth], m_pos_y[m_cardth]);
		this->addChild(card);
		m_cardth++;
	}else
	{
		this->unschedule(schedule_selector(RaffleTenLayer::show_box_card_front));
		m_cardth = 0;
		
		show_menu();
	}
}

void RaffleTenLayer::show_menu()
{
	auto button_normal = Sprite::createWithSpriteFrameName("button_little_0.png");
	auto button_pressed = Sprite::createWithSpriteFrameName("button_little_1.png");
	auto button_selected = Sprite::createWithSpriteFrameName("button_little_2.png");

	auto menuItem = MenuItemSprite::create(button_normal, button_pressed, button_selected);
	menuItem->setCallback([](Ref* pSender){
		Director::getInstance()->popScene();
	});

	auto text = Sprite::createWithSpriteFrameName("text_close.png");
	text->setPosition(button_normal->getContentSize().width/2, button_normal->getContentSize().height/2);
	menuItem->addChild(text);
	menuItem->setPosition(320, 150);
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
}