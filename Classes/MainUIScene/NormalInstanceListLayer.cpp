#include "NormalInstanceListLayer.h"


NormalInstanceListLayer::NormalInstanceListLayer(void)
{
}


NormalInstanceListLayer::~NormalInstanceListLayer(void)
{
}

bool NormalInstanceListLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	size = Director::getInstance()->getVisibleSize();


	//滑动条背景
	m_bTable = true;
	m_bSlider = true;
	auto sliderbk = Sprite::create("ui/scrollbar_0.png");
	sliderbk->setScaleY(7.0f);
	sliderbk->setPosition(size.width/2 + 295, size.height /2 - 240);
	this->addChild(sliderbk);

	//创建controlSlide，第一个参数为拖动前的背景图片，第二个参数为拖动后的背景图片，第三个参数为拖动杆
	slider = ControlSlider::create("ui/scrollbar_4.png", "ui/scrollbar_2.png", "ui/scrollbar_1.png");
	slider->setRotation(90);
	slider->setAnchorPoint(Vec2(0.5f, 1.0f));

	//TableView中单个Cell的高度 * cell的总数  - TableView 的高度;
	slider->setMinimumValue(-(110 * 21 - 500));
	slider->setMaximumValue(0);
	slider->setPosition(size.width/2 + 300, size.height/2 - 240);
	slider->setValue(-(110 * 21 - 500));
	slider->setTag(1);
	addChild(slider);

	//监听滚动条滚动事件
	slider->addTargetWithActionForControlEvents(this,cccontrol_selector(NormalInstanceListLayer::slideValueChanged),Control::EventType::VALUE_CHANGED);

	tableView = TableView::create(this, Size(600, 500));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL); //方向垂直
	tableView->setDelegate(this);
	tableView->setTag(1);
	addChild(tableView);

	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);  //填充次序从上到下
	tableView->reloadData();

	return true;
}

//滑动条滚动事件
void NormalInstanceListLayer::slideValueChanged(Ref* sender, Control::EventType type)
{
	log("slide value changed");
	m_bTable = false;
	if (m_bSlider)
	{
		tableView->setContentOffset(Size(0, slider->getValue()));
	}
	m_bTable = true;
}

//触摸到某个cell的事件
void NormalInstanceListLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	log("touch");
	NotificationCenter::getInstance()->postNotification("ReturnLineup");
}

//定制每个cell的size
Size NormalInstanceListLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	log("tableCellSizeForIndex");
	return Size(565, 110);
}

//定制每个cell的内容
TableViewCell* NormalInstanceListLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	auto cell = table->dequeueCell();
	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
		Node* item_node = getItemNode(idx);
		item_node->setPosition(Point::ZERO);
		item_node->setAnchorPoint(Point::ZERO);
		item_node->setTag(100);
		cell->addChild(item_node);
	}

	return cell;
}

//确定这个tableview的cell行数
ssize_t  NormalInstanceListLayer::numberOfCellsInTableView(TableView *table)
{
	log("numberOfCellsInTableView");
	return 21;
}

//设置单元格高亮的状态
void NormalInstanceListLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellHighlight");
	if (cell && cell->getActionByTag(100))
	{
		cell->getChildByTag(100)->getChildByTag(111)->setVisible(true);
	}
}

//设置单元格非高亮的状态
void NormalInstanceListLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellUnhighlight");
	if (cell && cell->getActionByTag(100))
	{
		cell->getChildByTag(100)->getChildByTag(111)->setVisible(false);
	}
}

//由于TableView是继承ScrollView，所以要继承这两个方法
//滑动tableView触发
void NormalInstanceListLayer::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidScroll");
	m_bSlider = false;
	if (m_bTable)
	{
		slider->setValue(tableView->getContentOffset().y);
	}
	m_bSlider = true;
}

void NormalInstanceListLayer::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidZoom");
}

Node* NormalInstanceListLayer::getItemNode(int i)
{
	auto item = Node::create();
	//Item背景
	auto item_bk = Sprite::createWithSpriteFrameName("button_rank_hero_0.png");
	item_bk->setAnchorPoint(Point::ZERO);
	item_bk->setPosition(Vec2(20 , 0));
	item->addChild(item_bk);

	//变亮的背景，点击就设visible为true，否则为false
	auto item_hi = Sprite::createWithSpriteFrameName("button_rank_hero_1.png");
	item_hi->setVisible(false);
	item_hi->setTag(111);
	item_hi->setAnchorPoint(Point::ZERO);
	item_hi->setPosition(Vec2(20, 0));
	item->addChild(item_hi);

	//关卡
	char ptext[30];
	sprintf(ptext, "normal_instance_%02d", i);
	std::string strtext = AppStringFile::getInstance()->getStringForKey(ptext);

	auto item_label_guanka = LabelTTF::create(strtext, "Arial", 30);
	item_label_guanka->setAnchorPoint(Point::ZERO);
	item_label_guanka->setPosition(45, 20);
	item->addChild(item_label_guanka);
	
	Sprite* item_pass;
	if (i == 20)
	{
		item_pass = Sprite::createWithSpriteFrameName("state_new.png");
	}else
	{
		item_pass = Sprite::createWithSpriteFrameName("state_complete.png");
	}
	item_pass->setPosition(20, 60);
	item_pass->setAnchorPoint(Point::ZERO);
	item->addChild(item_pass);

	
	return item;
}