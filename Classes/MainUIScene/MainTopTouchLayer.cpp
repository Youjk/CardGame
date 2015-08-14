#include "MainTopTouchLayer.h"
#include "Utils/AppStringFile.h"

MainTopTouchLayer::MainTopTouchLayer(void)
{
}


MainTopTouchLayer::~MainTopTouchLayer(void)
{
}

bool MainTopTouchLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	setContentSize(Size(640, 240));
	InitSysInfo();
	sysInfo->setVisible(false);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event){
		Vec2 position = touch->getLocationInView();
		if (position.y <= 130 && position.x >= 0)
		{
			sysInfo->setVisible(true);
			return true;
		}

		return false;
	};

	listener->onTouchEnded = [this](Touch* touch, Event* event){
		sysInfo->setVisible(false);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//初始化UI
void MainTopTouchLayer::InitSysInfo()
{
	sysInfo = Node::create();

	auto tipsbase = Sprite::createWithSpriteFrameName("tipsbase.png");
	tipsbase->setScaleY(1.5f);
	tipsbase->setAnchorPoint(Vec2(0.0, 1.0));
	tipsbase->setPosition(150, 780);
	sysInfo->addChild(tipsbase);

	std::string strText;
	//爵位信息
	strText = AppStringFile::getInstance()->getStringForKey("sysinfo_rank");
	auto sys_rank = LabelTTF::create(strText, "Arial", 20);
	sys_rank->setPosition(320, 750);
	sysInfo->addChild(sys_rank);

	//等级信息
	strText = AppStringFile::getInstance()->getStringForKey("sysinfo_level");
	auto sys_level = LabelTTF::create(strText, "Arial", 20);
	sys_level->setPosition(320, 722);
	sysInfo->addChild(sys_level);

	//魅力信息
	strText = AppStringFile::getInstance()->getStringForKey("sysinfo_charm");
	auto sys_charm = LabelTTF::create(strText, "Arial", 20);
	sys_charm->setPosition(320, 694);
	sysInfo->addChild(sys_charm);

	//经验信息
	strText = AppStringFile::getInstance()->getStringForKey("sysinfo_exp");
	auto sys_exp = LabelTTF::create(strText, "Arial", 20);
	sys_exp->setPosition(320, 666);
	sysInfo->addChild(sys_exp);

	//还需经验信息
	strText = AppStringFile::getInstance()->getStringForKey("sysinfo_needexp");
	auto sys_needexp = LabelTTF::create(strText, "Arial", 20);
	sys_needexp->setPosition(320, 638);
	sysInfo->addChild(sys_needexp);

	this->addChild(sysInfo);
}
