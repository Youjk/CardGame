#include "MyChipLayerList.h"
#include "Dialog/DialogLayer.h"
#include "Utils/AppStringFile.h"


MyChipLayerList::MyChipLayerList(void)
{
}


MyChipLayerList::~MyChipLayerList(void)
{
}

bool MyChipLayerList::init()
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
	sliderbk->setPosition(size.width/2 + 295, size.height /2 - 280);
	this->addChild(sliderbk);

	//����controlSlide����һ������Ϊ�϶�ǰ�ı���ͼƬ���ڶ�������Ϊ�϶���ı���ͼƬ������������Ϊ�϶���
	slider = ControlSlider::create("ui/scrollbar_4.png", "ui/scrollbar_2.png", "ui/scrollbar_1.png");
	slider->setRotation(90);
	slider->setAnchorPoint(Vec2(0.5f, 1.0f));

	//TableView�е���Cell�ĸ߶� * cell������  - TableView �ĸ߶�;
	slider->setMinimumValue(-(130 * 2 - 400));
	slider->setMaximumValue(0);
	slider->setPosition(size.width/2 + 300, size.height/2 - 240);
	slider->setValue(-(130 * 2 - 400));
	slider->setTag(1);
	slider->setVisible(false);
	addChild(slider);

	//���������������¼�
	slider->addTargetWithActionForControlEvents(this,cccontrol_selector(MyChipLayerList::slideValueChanged),Control::EventType::VALUE_CHANGED);

	tableView = TableView::create(this, Size(600, 500));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL); //����ֱ
	tableView->setDelegate(this);
	tableView->setTag(0);
	addChild(tableView);

	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);  //��������ϵ���
	tableView->reloadData();

	return true;
}

//�������仯
void MyChipLayerList::slideValueChanged(Ref* sender, Control::EventType type)
{
	m_bTable = false;
	if (m_bSlider)
	{
		tableView->setContentOffset(Size(0, slider->getValue()));
	}
	m_bTable = true;
}

//������ĳ��cell���¼�
void MyChipLayerList::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	if (cell->getIdx() == 0)
	{
		//�����Ի���
		DialogLayer* d = DialogLayer::create(Sprite::createWithSpriteFrameName("tipsbase.png"));
		d->setContentSize(Size(500, 200));
		d->setTitle(AppStringFile::getInstance()->getStringForKey("chip_success_tip").c_str());
		d->addButton("ok", 
			Sprite::createWithSpriteFrameName("button_0.png"),
			Sprite::createWithSpriteFrameName("button_2.png"),
			Sprite::createWithSpriteFrameName("button_2.png"),
			[d](Ref* pSender){
				d->removeFromParent();
		},0);
		Director::getInstance()->getRunningScene()->addChild(d);
	}
}

//����ÿ��cell��size
Size MyChipLayerList::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	return Size(543, 130);
}

//����ÿ��cell������
TableViewCell* MyChipLayerList::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	auto cell = table->dequeueCell();
	if (!cell)
	{
		cell = new TableViewCell();
		cell->autorelease();
		Node* item_node = getItemNode(idx);
		item_node->setPosition(Point::ZERO);
		item_node->setAnchorPoint(Point::ZERO);
		item_node->setTag(777);
		cell->addChild(item_node);
	}

	return cell;
}

//ȷ�����tableview��cell����
ssize_t MyChipLayerList::numberOfCellsInTableView(TableView *table)
{
	return 2;
}

//���õ�Ԫ�������״̬
void MyChipLayerList::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	cell->getChildByTag(777)->getChildByTag(888)->setVisible(true);
}
//���õ�Ԫ��Ǹ�����״̬
void MyChipLayerList::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	cell->getChildByTag(777)->getChildByTag(888)->setVisible(false);
}

//����TableView�Ǽ̳�ScrollView������Ҫ�̳�����������������ʱ�����
void MyChipLayerList::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
	m_bSlider = false;
	if (m_bTable)
	{
		slider->setValue(tableView->getContentOffset().y);
	}
	m_bSlider = true;
}

void MyChipLayerList::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{

}

Node* MyChipLayerList::getItemNode(int i)
{
	auto item = Node::create();
	//Item����
	auto item_bk = Sprite::create("ui/listbutton_base1.png");
	item_bk->setAnchorPoint(Point::ZERO);
	item_bk->setPosition(Vec2(20 , 0));
	item->addChild(item_bk);

	//�����ı������������visibleΪtrue������Ϊfalse
	auto item_hi = Sprite::createWithSpriteFrameName("listbutton_base1_1.png");
	item_hi->setVisible(false);
	item_hi->setTag(888);
	item_hi->setAnchorPoint(Point::ZERO);
	item_hi->setPosition(Vec2(20, 0));
	item->addChild(item_hi);

	//ͷ�񱳾���
	auto item_image_bk = Sprite::createWithSpriteFrameName("littlecard_base_class1.png");
	item_image_bk->setAnchorPoint(Vec2(Point::ZERO));
	item_image_bk->setPosition(15, 2);
	item->addChild(item_image_bk);

	//ͷ��
	Sprite* item_image;
	if (i == 0)
	{
		item_image = Sprite::create("ui/littlecard_0309.png");
	}else if(i == 1)
	{
		item_image = Sprite::create("ui/littlecard_0415.png");
	}
	item_image->setAnchorPoint(Point::ZERO);
	item_image->setPosition(15, 20);
	item->addChild(item_image);

	//С��Ƭ
	Sprite* item_image_chip = Sprite::createWithSpriteFrameName("littlecard_chip.png");
	item_image_chip->setAnchorPoint(Point::ZERO);
	item_image_chip->setPosition(10, 15);
	item->addChild(item_image_chip);

	//ͷ���
	auto  item_image_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class4.png");
	item_image_frame->setAnchorPoint(Point::ZERO);
	item_image_frame->setPosition(15, 20);
	item->addChild(item_image_frame);

	//����
	char chartext[20];
	sprintf(chartext, "chip_name_%d", i);
	std::string key(chartext);
	std::string value = AppStringFile::getInstance()->getStringForKey(key);
	auto item_name = LabelTTF::create(value, "Arial", 25);
	item_name->setTag(999);
	item_name->setAnchorPoint(Point::ZERO);
	item_name->setPosition(130, 90);
	item->addChild(item_name);

	//�����ȡ���
	std::string strtext = AppStringFile::getInstance()->getStringForKey("chip_progress_text");
	auto item_progress = LabelTTF::create(strtext, "Arial", 20);
	item_progress->setAnchorPoint(Point::ZERO);
	item_progress->setPosition(130, 60);
	item->addChild(item_progress);

	//��ʹ��������Ƭ
	strtext = AppStringFile::getInstance()->getStringForKey("chip_can_use");
	auto item_can_use = LabelTTF::create(strtext, "Arial", 20);
	item_can_use->setAnchorPoint(Point::ZERO);
	item_can_use->setPosition(130, 30);
	item->addChild(item_can_use);


	LabelTTF* item_progress_value;
	LabelTTF* item_canuse_value;
	Sprite* item_sign;

	if (i == 0)
	{
		item_progress_value = LabelTTF::create("30/5", "Arial", 20);
		item_canuse_value = LabelTTF::create("50", "Arial", 20);
		item_sign = Sprite::createWithSpriteFrameName("sign_complete1.png");
	}else
	{
		item_progress_value = LabelTTF::create("20/100", "Arial", 20);
		item_canuse_value = LabelTTF::create("50", "Arial", 20);
		item_sign = Sprite::createWithSpriteFrameName("sign_collect.png");
	}
	item_progress_value->setColor(Color3B(0, 200, 0));
	item_progress_value->setAnchorPoint(Point::ZERO);
	item_progress_value->setPosition(190, 60);
	item->addChild(item_progress_value);

	item_canuse_value ->setColor(Color3B(0, 200, 0));
	item_canuse_value ->setAnchorPoint(Point::ZERO);
	item_canuse_value ->setPosition(290, 30);
	item->addChild(item_canuse_value );

	item_sign->setAnchorPoint(Point::ZERO);
	item_sign->setPosition(400, 30);
	item->addChild(item_sign);

	return item;
}
