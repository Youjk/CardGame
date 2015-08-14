#include "TaskLayer.h"
#include "TaskListLayer.h"


TaskLayer::TaskLayer(void)
{
}


TaskLayer::~TaskLayer(void)
{
}

bool TaskLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initframe();

	auto backlistener = EventListenerKeyboard::create();
	backlistener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event){
		switch(keyCode)
		{        
			//�������ؼ�        
		case EventKeyboard::KeyCode::KEY_ESCAPE:              
			Director::getInstance()->popScene();            
			break;        
			//����menu��        
		case EventKeyboard::KeyCode::KEY_MENU:             
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backlistener, this);
	return true;
}

void TaskLayer::initframe()
{
	Size size = Director::getInstance()->getVisibleSize();


	//����
	auto background = Sprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(size.width/2, 760);
	this->addChild(background);

	//��������
	auto listbase = Sprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(size.width/2, 410);
	this->addChild(listbase);

	//����
	TaskListLayer* tasklayer = TaskListLayer::create();
	tasklayer->setPosition(20,150);
	this->addChild(tasklayer);

	//�ײ�����
	auto bottom_list = Sprite::createWithSpriteFrameName("bottom_list.jpg");
	bottom_list->setPosition(size.width/2, bottom_list->getContentSize().height/2);
	this->addChild(bottom_list);

	//�������ֵı���
	auto middletitlebase = Sprite::createWithSpriteFrameName("middletitlebase.png");
	middletitlebase->setPosition(size.width/2, 700);
	this->addChild(middletitlebase);

	//����������
	auto titletext = Sprite::createWithSpriteFrameName("titlename_task.png");
	titletext->setPosition(size.width/2, 690);
	this->addChild(titletext);


	//�������ذ�ť
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
}


