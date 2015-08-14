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


	//����������
	m_bTable = true;
	m_bSlider = true;
	auto sliderbk = Sprite::create("ui/scrollbar_0.png");
	sliderbk->setScaleY(7.0f);
	sliderbk->setPosition(size.width/2 + 295, size.height /2 - 240);
	this->addChild(sliderbk);

	//����controlSlide����һ������Ϊ�϶�ǰ�ı���ͼƬ���ڶ�������Ϊ�϶���ı���ͼƬ������������Ϊ�϶���
	slider = ControlSlider::create("ui/scrollbar_4.png", "ui/scrollbar_2.png", "ui/scrollbar_1.png");
	slider->setRotation(90);
	slider->setAnchorPoint(Vec2(0.5f, 1.0f));

	//TableView�е���Cell�ĸ߶� * cell������  - TableView �ĸ߶�;
	slider->setMinimumValue(-(110 * 21 - 500));
	slider->setMaximumValue(0);
	slider->setPosition(size.width/2 + 300, size.height/2 - 240);
	slider->setValue(-(110 * 21 - 500));
	slider->setTag(1);
	addChild(slider);

	//���������������¼�
	slider->addTargetWithActionForControlEvents(this,cccontrol_selector(NormalInstanceListLayer::slideValueChanged),Control::EventType::VALUE_CHANGED);

	tableView = TableView::create(this, Size(600, 500));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL); //����ֱ
	tableView->setDelegate(this);
	tableView->setTag(1);
	addChild(tableView);

	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);  //��������ϵ���
	tableView->reloadData();

	return true;
}

//�����������¼�
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

//������ĳ��cell���¼�
void NormalInstanceListLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	log("touch");
	NotificationCenter::getInstance()->postNotification("ReturnLineup");
}

//����ÿ��cell��size
Size NormalInstanceListLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	log("tableCellSizeForIndex");
	return Size(565, 110);
}

//����ÿ��cell������
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

//ȷ�����tableview��cell����
ssize_t  NormalInstanceListLayer::numberOfCellsInTableView(TableView *table)
{
	log("numberOfCellsInTableView");
	return 21;
}

//���õ�Ԫ�������״̬
void NormalInstanceListLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellHighlight");
	if (cell && cell->getActionByTag(100))
	{
		cell->getChildByTag(100)->getChildByTag(111)->setVisible(true);
	}
}

//���õ�Ԫ��Ǹ�����״̬
void NormalInstanceListLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellUnhighlight");
	if (cell && cell->getActionByTag(100))
	{
		cell->getChildByTag(100)->getChildByTag(111)->setVisible(false);
	}
}

//����TableView�Ǽ̳�ScrollView������Ҫ�̳�����������
//����tableView����
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
	//Item����
	auto item_bk = Sprite::createWithSpriteFrameName("button_rank_hero_0.png");
	item_bk->setAnchorPoint(Point::ZERO);
	item_bk->setPosition(Vec2(20 , 0));
	item->addChild(item_bk);

	//�����ı������������visibleΪtrue������Ϊfalse
	auto item_hi = Sprite::createWithSpriteFrameName("button_rank_hero_1.png");
	item_hi->setVisible(false);
	item_hi->setTag(111);
	item_hi->setAnchorPoint(Point::ZERO);
	item_hi->setPosition(Vec2(20, 0));
	item->addChild(item_hi);

	//�ؿ�
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