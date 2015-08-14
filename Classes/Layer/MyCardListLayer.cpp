#include "MyCardListLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;

MyCardListLayer::MyCardListLayer(void)
{

}



MyCardListLayer::~MyCardListLayer(void)
{
}

bool MyCardListLayer::init()
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
	slider->setMinimumValue(-(110 * 14 - 500));
	slider->setMaximumValue(0);
	slider->setPosition(size.width/2 + 300, size.height/2 - 240);
	slider->setValue(0);
	slider->setTag(1);
	addChild(slider);

	//监听滚动条滚动事件
	slider->addTargetWithActionForControlEvents(this,cccontrol_selector(MyCardListLayer::slideValueChanged),Control::EventType::VALUE_CHANGED);
	
	tableView = TableView::create(this, Size(600, 500));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL); //方向垂直
	tableView->setDelegate(this);
	tableView->setTag(0);
	addChild(tableView);

	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);  //填充次序从上到下
	tableView->reloadData();

	return true;
}

//滑动条滚动事件
void MyCardListLayer::slideValueChanged(Ref* sender, Control::EventType type)
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
void MyCardListLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	log("tableCellTouched index : %i", cell->getIdx());
}

//定制每个cell的size
Size MyCardListLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	log("tableCellSizeForIndex");
	return Size(565, 110);
}

//定制每个cell的内容
TableViewCell* MyCardListLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	//'poreturn TableView::create()
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
ssize_t  MyCardListLayer::numberOfCellsInTableView(TableView *table)
{
	log("numberOfCellsInTableView");
	return 14;
}

//设置单元格高亮的状态
void MyCardListLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellHighlight");
	cell->getChildByTag(100)->getChildByTag(111)->setVisible(true);
}

//设置单元格非高亮的状态
void MyCardListLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellUnhighlight");
	cell->getChildByTag(100)->getChildByTag(111)->setVisible(false);
}

//由于TableView是继承ScrollView，所以要继承这两个方法
//滑动tableView触发
void MyCardListLayer::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidScroll");
	m_bSlider = false;
	if (m_bTable)
	{
		slider->setValue(tableView->getContentOffset().y);
	}
	m_bSlider = true;
}

void MyCardListLayer::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidZoom");
}

Node* MyCardListLayer::getItemNode(int i)
{
	auto item = Node::create();
	//Item背景
	auto item_bk = Sprite::createWithSpriteFrameName("button_public_rank_0.png");
	item_bk->setAnchorPoint(Point::ZERO);
	item_bk->setPosition(Vec2(20 , 0));
	item->addChild(item_bk);

	//变亮的背景，点击就设visible为true，否则为false
	auto item_hi = Sprite::createWithSpriteFrameName("button_public_rank_1.png");
	item_hi->setVisible(false);
	item_hi->setTag(111);
	item_hi->setAnchorPoint(Point::ZERO);
	item_hi->setPosition(Vec2(20, 0));
	item->addChild(item_hi);

	//头像背景
	auto item_image_bk = Sprite::createWithSpriteFrameName("littlecard_base_class1.png");
	item_image_bk->setScale(1.1f);
	item_image_bk->setAnchorPoint(Vec2(Point::ZERO));
	item_image_bk->setPosition(15, 2);
	item->addChild(item_image_bk);

	//头像
	char cardname[30];
	sprintf(cardname, "ui/littlecard_03%02d.png", 29 + i * 2);
	auto item_image = Sprite::create(cardname);
	item_image->setTag(222);
	item_image->setAnchorPoint(Point::ZERO);
	item_image->setPosition(15, 2);
	item->addChild(item_image);

	//头像框
	auto  item_image_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class4_elite.png");
	item_image_frame->setAnchorPoint(Point::ZERO);
	item_image_frame->setPosition(15, 2);
	item->addChild(item_image_frame);

	//名字
	char chartext[20];
	sprintf(chartext, "my_card_name_%02d", i);
	std::string key(chartext);
	std::string value = AppStringFile::getInstance()->getStringForKey(key);
	auto item_name = LabelTTF::create(value, "Arial", 25);
	item_name->setTag(333);
	item_name->setAnchorPoint(Point::ZERO);
	item_name->setPosition(160, 60);
	item->addChild(item_name);

	//等级名
	auto item_Lv_text = Sprite::createWithSpriteFrameName("lv.png");
	item_Lv_text->setAnchorPoint(Point::ZERO);
	item_Lv_text->setPosition(30, 10);
	item->addChild(item_Lv_text);
	//等级值
	auto item_LV_value = LabelTTF::create("1", "Arial", 20);
	item_LV_value->setAnchorPoint(Point::ZERO);
	item_LV_value->setPosition(80, 10);
	item->addChild(item_LV_value);

	//人物右下角的那个图标
	auto item_occupation = Sprite::createWithSpriteFrameName(spritename[i]);
	item_occupation->setTag(444);
	item_occupation->setScale(1.2f);
	item_occupation->setPosition(115, 50);
	item->addChild(item_occupation);

	//血值
	auto item_blood_value = LabelTTF::create("9999", "Arial", 25);
	item_blood_value->setAnchorPoint(Point::ZERO);
	item_blood_value->setPosition(160, 20);
	item->addChild(item_blood_value);

	//攻击值
	auto item_attack_value = LabelTTF::create("6666", "Arial", 25);
	item_attack_value->setAnchorPoint(Point::ZERO);
	item_attack_value->setPosition(280, 20);
	item->addChild(item_attack_value);

	for (int i = 0; i < 5; ++i)
	{
		auto item_start = Sprite::createWithSpriteFrameName("littlestar.png");
		item_start->setPosition(400 + i * 30, 30);
		item_start->setAnchorPoint(Point::ZERO);
		item->addChild(item_start);
	}
	return item;
}