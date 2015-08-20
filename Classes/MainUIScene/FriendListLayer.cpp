#include "FriendListLayer.h"
#include "Utils/AppStringFile.h"


FriendListLayer::FriendListLayer(void)
{
}


FriendListLayer::~FriendListLayer(void)
{

}


bool FriendListLayer::init()
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
	sliderbk->setScaleY(5.5f);
	sliderbk->setPosition(size.width/2 + 295, size.height /2 - 280);
	this->addChild(sliderbk);

	//����controlSlide����һ������Ϊ�϶�ǰ�ı���ͼƬ���ڶ�������Ϊ�϶���ı���ͼƬ������������Ϊ�϶���
	slider = ControlSlider::create("ui/scrollbar_4.png", "ui/scrollbar_2.png", "ui/scrollbar_1.png");
	slider->setRotation(90);
	slider->setAnchorPoint(Vec2(0.5f, 1.0f));

	//TableView�е���Cell�ĸ߶� * cell������  - TableView �ĸ߶�;
	slider->setMinimumValue(-(120 * 20 - 400));
	slider->setMaximumValue(0);
	slider->setPosition(size.width/2 + 300, size.height/2 - 280);
	slider->setValue(-(120 * 20 - 400));
	slider->setTag(1);
	addChild(slider);

	//���������������¼�
	slider->addTargetWithActionForControlEvents(this,cccontrol_selector(FriendListLayer::slideValueChanged),Control::EventType::VALUE_CHANGED);

	tableView = TableView::create(this, Size(600, 400));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL); //����ֱ
	tableView->setDelegate(this);
	tableView->setTag(0);
	addChild(tableView);

	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);  //��������ϵ���
	tableView->reloadData();

	return true;
}

//�����������¼�
void FriendListLayer::slideValueChanged(Ref* sender, Control::EventType type)
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
void FriendListLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	log("tableCellTouched index : %i", cell->getIdx());
}

//����ÿ��cell��size
Size FriendListLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	log("tableCellSizeForIndex");
	return Size(565, 110);
}

//����ÿ��cell������
TableViewCell* FriendListLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
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
		item_node->setTag(777);
		cell->addChild(item_node);
	}else
	{
		auto label = (LabelTTF*)(cell->getChildByTag(777)->getChildByTag(999));
	}

	return cell;
}

//ȷ�����tableview��cell����
ssize_t  FriendListLayer::numberOfCellsInTableView(TableView *table)
{
	log("numberOfCellsInTableView");
	return 20;
}

//���õ�Ԫ�������״̬
void FriendListLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellHighlight");
	cell->getChildByTag(777)->getChildByTag(888)->setVisible(true);
}

//���õ�Ԫ��Ǹ�����״̬
void FriendListLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellUnhighlight");
	cell->getChildByTag(777)->getChildByTag(888)->setVisible(false);
}

//����TableView�Ǽ̳�ScrollView������Ҫ�̳�����������
//����tableView����
void FriendListLayer::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidScroll");
	m_bSlider = false;
	if (m_bTable)
	{
		slider->setValue(tableView->getContentOffset().y);
	}
	m_bSlider = true;
}

void FriendListLayer::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidZoom");
}

Node* FriendListLayer::getItemNode(int i)
{
	auto item = Node::create();
	//Item����
	auto item_bk = Sprite::createWithSpriteFrameName("button_public_rank1_0.png");
	item_bk->setAnchorPoint(Point::ZERO);
	item_bk->setPosition(Vec2(20 , 0));
	item->addChild(item_bk);

	//�����ı������������visibleΪtrue������Ϊfalse
	auto item_hi = Sprite::createWithSpriteFrameName("button_public_rank1_1.png");
	item_hi->setVisible(false);
	item_hi->setTag(888);
	item_hi->setAnchorPoint(Point::ZERO);
	item_hi->setPosition(Vec2(20, 0));
	item->addChild(item_hi);

	//ͷ�񱳾�
	auto item_image_bk = Sprite::createWithSpriteFrameName("littlecard_base_class1.png");
	item_image_bk->setAnchorPoint(Vec2(Point::ZERO));
	item_image_bk->setPosition(15, 5);
	item->addChild(item_image_bk);

	//ͷ��
	auto item_image = Sprite::create("ui/littlecard_0347.png");
	item_image->setAnchorPoint(Point::ZERO);
	item_image->setPosition(15, 5);
	item->addChild(item_image);

	//ͷ���
	auto  item_image_frame = Sprite::createWithSpriteFrameName("littlecard_frame_class4_elite.png");
	item_image_frame->setAnchorPoint(Point::ZERO);
	item_image_frame->setPosition(15, 5);
	item->addChild(item_image_frame);

	//����
	char chartext[10];
	sprintf(chartext, "yjk_%d", i);
	auto item_name = LabelTTF::create(chartext, "Arial", 25);
	item_name->setTag(333);
	item_name->setAnchorPoint(Point::ZERO);
	item_name->setPosition(160, 60);
	item->addChild(item_name);
	
	std::string strText = AppStringFile::getInstance()->getStringForKey("friend_logininfo_01");
	auto item_logininfo = LabelTTF::create(strText, "Arial", 25);
	item_logininfo->setAnchorPoint(Point::ZERO);
	item_logininfo->setColor(Color3B(0, 200, 0));
	item_logininfo->setPosition(120, 20);
	item->addChild(item_logininfo);

	strText = AppStringFile::getInstance()->getStringForKey("friend_level_01");
	auto item_level = LabelTTF::create(strText, "Arial", 25);
	item_level->setAnchorPoint(Point::ZERO);
	item_level->setPosition(480, 60);
	item->addChild(item_level);;

	auto item_occupation = Sprite::createWithSpriteFrameName("icon_occupation_rogue_button.png");
	item_occupation->setAnchorPoint(Point::ZERO);
	item_occupation->setPosition(115, 50);
	item->setScale(1.2f);
	item->addChild(item_occupation);


	auto item_rank = Sprite::createWithSpriteFrameName("rank_9.png");
	item_rank->setAnchorPoint(Point::ZERO);
	item_rank->setPosition(350, 57);
	item->addChild(item_rank);
	return item;
}
