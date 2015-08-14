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
	slider->setMinimumValue(-(110 * 14 - 500));
	slider->setMaximumValue(0);
	slider->setPosition(size.width/2 + 300, size.height/2 - 240);
	slider->setValue(0);
	slider->setTag(1);
	addChild(slider);

	//���������������¼�
	slider->addTargetWithActionForControlEvents(this,cccontrol_selector(MyCardListLayer::slideValueChanged),Control::EventType::VALUE_CHANGED);
	
	tableView = TableView::create(this, Size(600, 500));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL); //����ֱ
	tableView->setDelegate(this);
	tableView->setTag(0);
	addChild(tableView);

	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);  //��������ϵ���
	tableView->reloadData();

	return true;
}

//�����������¼�
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

//������ĳ��cell���¼�
void MyCardListLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	log("tableCellTouched index : %i", cell->getIdx());
}

//����ÿ��cell��size
Size MyCardListLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	log("tableCellSizeForIndex");
	return Size(565, 110);
}

//����ÿ��cell������
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

//ȷ�����tableview��cell����
ssize_t  MyCardListLayer::numberOfCellsInTableView(TableView *table)
{
	log("numberOfCellsInTableView");
	return 14;
}

//���õ�Ԫ�������״̬
void MyCardListLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellHighlight");
	cell->getChildByTag(100)->getChildByTag(111)->setVisible(true);
}

//���õ�Ԫ��Ǹ�����״̬
void MyCardListLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellUnhighlight");
	cell->getChildByTag(100)->getChildByTag(111)->setVisible(false);
}

//����TableView�Ǽ̳�ScrollView������Ҫ�̳�����������
//����tableView����
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
	//Item����
	auto item_bk = Sprite::createWithSpriteFrameName("button_public_rank_0.png");
	item_bk->setAnchorPoint(Point::ZERO);
	item_bk->setPosition(Vec2(20 , 0));
	item->addChild(item_bk);

	//�����ı������������visibleΪtrue������Ϊfalse
	auto item_hi = Sprite::createWithSpriteFrameName("button_public_rank_1.png");
	item_hi->setVisible(false);
	item_hi->setTag(111);
	item_hi->setAnchorPoint(Point::ZERO);
	item_hi->setPosition(Vec2(20, 0));
	item->addChild(item_hi);

	//ͷ�񱳾�
	auto item_image_bk = Sprite::createWithSpriteFrameName("littlecard_base_class1.png");
	item_image_bk->setScale(1.1f);
	item_image_bk->setAnchorPoint(Vec2(Point::ZERO));
	item_image_bk->setPosition(15, 2);
	item->addChild(item_image_bk);

	//ͷ��
	char cardname[30];
	sprintf(cardname, "ui/littlecard_03%02d.png", 29 + i * 2);
	auto item_image = Sprite::create(cardname);
	item_image->setTag(222);
	item_image->setAnchorPoint(Point::ZERO);
	item_image->setPosition(15, 2);
	item->addChild(item_image);

	//ͷ���
	auto  item_image_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class4_elite.png");
	item_image_frame->setAnchorPoint(Point::ZERO);
	item_image_frame->setPosition(15, 2);
	item->addChild(item_image_frame);

	//����
	char chartext[20];
	sprintf(chartext, "my_card_name_%02d", i);
	std::string key(chartext);
	std::string value = AppStringFile::getInstance()->getStringForKey(key);
	auto item_name = LabelTTF::create(value, "Arial", 25);
	item_name->setTag(333);
	item_name->setAnchorPoint(Point::ZERO);
	item_name->setPosition(160, 60);
	item->addChild(item_name);

	//�ȼ���
	auto item_Lv_text = Sprite::createWithSpriteFrameName("lv.png");
	item_Lv_text->setAnchorPoint(Point::ZERO);
	item_Lv_text->setPosition(30, 10);
	item->addChild(item_Lv_text);
	//�ȼ�ֵ
	auto item_LV_value = LabelTTF::create("1", "Arial", 20);
	item_LV_value->setAnchorPoint(Point::ZERO);
	item_LV_value->setPosition(80, 10);
	item->addChild(item_LV_value);

	//�������½ǵ��Ǹ�ͼ��
	auto item_occupation = Sprite::createWithSpriteFrameName(spritename[i]);
	item_occupation->setTag(444);
	item_occupation->setScale(1.2f);
	item_occupation->setPosition(115, 50);
	item->addChild(item_occupation);

	//Ѫֵ
	auto item_blood_value = LabelTTF::create("9999", "Arial", 25);
	item_blood_value->setAnchorPoint(Point::ZERO);
	item_blood_value->setPosition(160, 20);
	item->addChild(item_blood_value);

	//����ֵ
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