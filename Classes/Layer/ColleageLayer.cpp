#include "ColleageLayer.h"
#include "Utils/AppStringFile.h"

ColleageLayer::ColleageLayer(void)
{
}


ColleageLayer::~ColleageLayer(void)
{
}

bool ColleageLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initframe();
	initcard();
	inittext();

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

void ColleageLayer::initframe()
{
	Size size = Director::getInstance()->getVisibleSize();

	//背景
	auto background = Sprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(size.width/2, 760);
	this->addChild(background);

	//技能学院背景
	auto listbase = Sprite::create("ui/collegebase.jpg");
	listbase->setScale(1.3f);
	listbase->setPosition(size.width/2, 400);
	this->addChild(listbase);

	//底部背景
	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);
	this->addChild(bottom_list);

	//顶部文字的背景
	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);

	//文本合成
	auto titletext = Sprite::createWithSpriteFrameName("titlename_college.png");
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
	text_return->setPosition(button_left_normal->getContentSize().width/2 - 15, button_left_normal->getContentSize().height/2);
	menuItem->addChild(text_return);

	auto menu_left = Menu::create(menuItem, NULL);
	menu_left->setPosition(menuItem->getContentSize().width/2 - 10, 687);
	this->addChild(menu_left);


	//顶部帮助按钮
	auto button_right_normal = Sprite::createWithSpriteFrameName("button_help_0.png");
	auto button_right_pressed = Sprite::createWithSpriteFrameName("button_help_1.png");
	auto button_right_disable = Sprite::createWithSpriteFrameName("button_help_0.png");
	auto button_right_menuItem = MenuItemSprite::create(button_right_normal, button_right_pressed, button_right_disable);
	button_right_menuItem->setCallback(CC_CALLBACK_1(ColleageLayer::menu_help_callback, this));
	auto menu_right = Menu::create(button_right_menuItem, NULL);
	menu_right->setPosition(size.width - button_right_menuItem->getContentSize().width /2 + 20, 687);
	this->addChild(menu_right);

	//重置按钮
	auto button_reset_normal = Sprite::createWithSpriteFrameName("button_little_0.png");
	auto button_reset_pressed = Sprite::createWithSpriteFrameName("button_little_1.png");
	auto button_reset_disable = Sprite::createWithSpriteFrameName("button_little_2.png");
	reset_Item = MenuItemSprite::create(button_reset_normal, button_reset_pressed, button_reset_disable);
	reset_Item->setScale(0.8f);

	auto text_reset = Sprite::createWithSpriteFrameName("text_reset.png");
	text_reset->setPosition(button_reset_normal->getContentSize().width/2 - 15, button_reset_normal->getContentSize().height/2);
	reset_Item->addChild(text_reset);

	reset_Item->setCallback(CC_CALLBACK_1(ColleageLayer::menu_reset_callback, this));
	auto menu_reset = Menu::create(reset_Item, NULL);
	menu_reset->setPosition(size.width / 2 - 150, 193);
	this->addChild(menu_reset);

	//学习按钮
	auto button_learn_normal = Sprite::createWithSpriteFrameName("button_little_0.png");
	auto button_learn_pressed = Sprite::createWithSpriteFrameName("button_little_1.png");
	auto button_learn_disable = Sprite::createWithSpriteFrameName("button_little_2.png");
	learn_Item = MenuItemSprite::create(button_learn_normal, button_learn_pressed, button_learn_disable);
	learn_Item->setScale(0.8f);
	learn_Item->setEnabled(false);

	auto text_learn = Sprite::createWithSpriteFrameName("text_learn.png");
	text_learn->setPosition(button_learn_normal->getContentSize().width/2 - 15, button_learn_normal->getContentSize().height/2);
	learn_Item->addChild(text_learn);

	learn_Item->setCallback(CC_CALLBACK_1(ColleageLayer::menu_learn_callback, this));
	auto menu_learn = Menu::create(learn_Item, NULL);
	menu_learn->setPosition(size.width / 2 + 150, 193);
	this->addChild(menu_learn);
}

void ColleageLayer::initcard()
{
	Node* card = Node::create();
	
	//卡牌框
	auto frame = Sprite::createWithSpriteFrameName("bigcard_frame_class2.png");
	frame->setScale(1.1f);
	card->addChild(frame);

	//卡牌内容
	auto card_content =Sprite::createWithSpriteFrameName("bigcard_0351.png");
	card_content->setPosition(0, -10);
	card->addChild(card_content);

	//勋章
	auto occupation = Sprite::createWithSpriteFrameName("icon_occupation_base4.png");
	occupation->setPosition(23, -25);
	occupation->setScale(1.3f);
	card->addChild(occupation);

	auto occupation_warrior_before = Sprite::createWithSpriteFrameName("icon_occupation_mage_button.png");
	occupation_warrior_before->setScale(1.6f);
	occupation_warrior_before->setPosition(73, -88);
	card->addChild(occupation_warrior_before);

	card->setScale(0.85f);
	card->setPosition(123, 517);
	this->addChild(card);
}

void ColleageLayer::inittext()
{
	//旧有技能
	std::string strtext = AppStringFile::getInstance()->getStringForKey("colleage_skill_origin");
	origin_skill = LabelTTF::create(strtext, "Arial", 20);
	origin_skill->setColor(Color3B(0, 200, 0));
	origin_skill->setAnchorPoint(Vec2(0, 0.5));
	origin_skill->setPosition(250, 570);
	this->addChild(origin_skill);

	strtext = AppStringFile::getInstance()->getStringForKey("colleage_skill_origin_describe");
	origin_skill_describe = LabelTTF::create(strtext, "Arial", 20);
	origin_skill_describe->setAnchorPoint(Vec2(0, 0.5));
	origin_skill_describe->setPosition(250, 530);
	this->addChild(origin_skill_describe);

	//无技能
	strtext = AppStringFile::getInstance()->getStringForKey("colleage_skill_none_describe");
	none_describe = LabelTTF::create(strtext, "Arial", 20);
	none_describe->setAnchorPoint(Vec2(0, 0.5));
	none_describe->setPosition(110,305);
	this->addChild(none_describe);
}

//帮助按钮回调
void ColleageLayer::menu_help_callback(Ref* pSender)
{

}

 //重置按钮回调
void ColleageLayer::menu_reset_callback(Ref* pSender)
{
	if (none_describe)
	{
		auto none_blink = Blink::create(1.0f, 2);
		auto none_blink_done =CallFunc::create([this](){
			none_describe->setVisible(false);

			std::string strtext = AppStringFile::getInstance()->getStringForKey("colleage_skill_new");
			new_skill = LabelTTF::create(strtext, "Arial", 20);
			new_skill->setColor(Color3B(255, 0, 0));
			new_skill->setAnchorPoint(Vec2(0, 0.5));
			new_skill->setPosition(110, 345);
			this->addChild(new_skill);

			strtext = AppStringFile::getInstance()->getStringForKey("colleage_skill_new_describe");
			new_skill_describe = LabelTTF::create(strtext, "Arial", 20);
			new_skill_describe->setAnchorPoint(Vec2(0, 0.5));
			new_skill_describe->setPosition(110, 305);
			this->addChild(new_skill_describe);

			learn_Item->setEnabled(true);
		});
		auto sequence = Sequence::create(none_blink, none_blink_done, NULL);
		none_describe->runAction(sequence);
	}
}

//学习按钮回调
void ColleageLayer::menu_learn_callback(Ref* pSender)
{
	if (new_skill)
	{
		auto new_skill_blink = Blink::create(1.0f, 2);
		new_skill->runAction(new_skill_blink);

		auto new_skill_describe_blink = new_skill_blink->clone();
		auto blink_done = CallFunc::create([this](){
			this->removeChild(new_skill_describe);
			this->removeChild(new_skill);
			new_skill_describe = NULL;
			new_skill = NULL;

			none_describe->setVisible(true);

			//改变旧的技能文字
			std::string strtext = AppStringFile::getInstance()->getStringForKey("colleage_skill_new");
			origin_skill->setString(strtext);
			origin_skill->setColor(Color3B(255, 0, 0));
			origin_skill->runAction(Blink::create(1.0f, 2));

			strtext = AppStringFile::getInstance()->getStringForKey("colleage_skill_new_describe");
			origin_skill_describe ->setString(strtext);
			origin_skill_describe ->runAction(Blink::create(1.0f, 2));
		});

		auto sequence = Sequence::create(new_skill_describe_blink, blink_done, NULL);
		new_skill_describe->runAction(sequence);

		magic = Sprite::create("ui/collegebase_02_16_9.png");
		magic->setPosition(530, 270);
		this->addChild(magic, 2);

		auto magic_done = CallFunc::create([this](){
			this->removeChild(magic);
		});

		auto magic_sequence = Sequence::create(ScaleTo::create(1, 0.2f), magic_done, NULL);
		magic->runAction(magic_sequence);

		book = Sprite::create("ui/college_5.png");
		book->setScale(1.1f);
		book->setPosition(520, 290);
		this->addChild(book);
		auto book_done = CallFunc::create([this](){
			this->removeChild(book);
		});
		auto book_sequence = Sequence::create(ScaleTo::create(1, 1.0f), book_done, NULL);
		book->runAction(book_sequence);

		learn_Item->setEnabled(false);
		reset_Item->setEnabled(false);
	}

}
