#include "MoreListLayer.h"
#include "Utils/AppStringFile.h"


MoreListLayer::MoreListLayer(void)
{
}


MoreListLayer::~MoreListLayer(void)
{

}


bool MoreListLayer::init()
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
	slider = ControlSlider::create("ui/scrollbar_4.png", "ui/scrollbar_2.png", "ui/scrollbar_5.png");
	slider->setRotation(90);
	slider->setAnchorPoint(Vec2(0.5f, 1.0f));

	//TableView中单个Cell的高度 * cell的总数  - TableView 的高度;
	slider->setMinimumValue(-(120 * 6 - 500));
	slider->setMaximumValue(0);
	slider->setPosition(size.width/2 + 300, size.height/2 - 240);
	slider->setValue(-(120 * 6 - 500));
	slider->setTag(1);
	addChild(slider);

	//监听滚动条滚动事件
	slider->addTargetWithActionForControlEvents(this,cccontrol_selector(MoreListLayer::slideValueChanged),Control::EventType::VALUE_CHANGED);

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
void MoreListLayer::slideValueChanged(Ref* sender, Control::EventType type)
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
void MoreListLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	log("tableCellTouched index : %i", cell->getIdx());
}

//定制每个cell的size
Size MoreListLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	log("tableCellSizeForIndex");
	return Size(565, 120);
}

//定制每个cell的内容
TableViewCell* MoreListLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
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
	}else
	{
		Sprite* item_image_sprite;
		switch (idx)
		{
		case 0:
			item_image_sprite = Sprite::createWithSpriteFrameName("icon_invite.png");
			break;
		case 1:
			item_image_sprite = Sprite::createWithSpriteFrameName("icon_placard.png");
			break;
		case 2:
			item_image_sprite = Sprite::createWithSpriteFrameName("icon_handbook.png");
			break;
		case 3:
			item_image_sprite = Sprite::createWithSpriteFrameName("icon_plaequipment.png");
			break;
		case 4:
			item_image_sprite = Sprite::createWithSpriteFrameName("icon_setting.png");
			break;
		case 5:
			item_image_sprite = Sprite::createWithSpriteFrameName("icon_moregame.png");
			break;
		default:
			break;
		}

		auto itemImageTexture = item_image_sprite->getTexture();
		auto pSprite = (Sprite*)(cell->getChildByTag(100)->getChildByTag(333));
		pSprite->setTexture(itemImageTexture);

		char chartext[15];
		sprintf(chartext, "more_0%d_text", idx);
		const char* p = chartext;
		std::string s_text(p);
		std::string strText = AppStringFile::getInstance()->getStringForKey(s_text);
		auto pLabel = (LabelTTF*)(cell->getChildByTag(100)->getChildByTag(444));
		pLabel->setString(strText);
	}

	return cell;
}

//确定这个tableview的cell行数
ssize_t  MoreListLayer::numberOfCellsInTableView(TableView *table)
{
	log("numberOfCellsInTableView");
	return 6;
}

//设置单元格高亮的状态
void MoreListLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellHighlight");
	cell->getChildByTag(100)->getChildByTag(888)->setVisible(true);
}

//设置单元格非高亮的状态
void MoreListLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellUnhighlight");
	cell->getChildByTag(100)->getChildByTag(888)->setVisible(false);
}

//由于TableView是继承ScrollView，所以要继承这两个方法
//滑动tableView触发
void MoreListLayer::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidScroll");
	m_bSlider = false;
	if (m_bTable)
	{
		slider->setValue(tableView->getContentOffset().y);
	}
	m_bSlider = true;
}

void MoreListLayer::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidZoom");
}

Node* MoreListLayer::getItemNode(int i)
{
	auto item = Node::create();
	//Item背景
	auto item_bk = Sprite::createWithSpriteFrameName("button_public_rank2_0.png");
	item_bk->setAnchorPoint(Point::ZERO);
	item_bk->setPosition(Vec2(20 , 0));
	item->addChild(item_bk);

	//变亮的背景，点击就设visible为true，否则为false
	auto item_hi = Sprite::createWithSpriteFrameName("button_public_rank2_1.png");
	item_hi->setVisible(false);
	item_hi->setTag(888);
	item_hi->setAnchorPoint(Point::ZERO);
	item_hi->setPosition(Vec2(20, 0));
	item->addChild(item_hi);

	//头像框
	auto  item_image_frame = Sprite::createWithSpriteFrameName("button_iconframe.png");
	item_image_frame->setTag(222);
	item_image_frame->setAnchorPoint(Point::ZERO);
	item_image_frame->setPosition(15, 2);
	item->addChild(item_image_frame);

	
	Sprite* item_image;
	switch (i)
	{
	case 0:
		item_image = Sprite::createWithSpriteFrameName("icon_invite.png");
		break;
	case 1:
		item_image = Sprite::createWithSpriteFrameName("icon_placard.png");
		break;
	case 2:
		item_image = Sprite::createWithSpriteFrameName("icon_handbook.png");
		break;
	case 3:
		item_image = Sprite::createWithSpriteFrameName("icon_plaequipment.png");
		break;
	case 4:
		item_image = Sprite::createWithSpriteFrameName("icon_setting.png");
		break;
	case 5:
		item_image = Sprite::createWithSpriteFrameName("icon_moregame.png");
		break;
	default:
		break;
	}
	item_image->setTag(333);
	item_image->setAnchorPoint(Point::ZERO);
	item_image->setPosition(18, 7);
	item->addChild(item_image);

	//名字
	char chartext[15];
	sprintf(chartext, "more_0%d_text", i);
	std::string strText = AppStringFile::getInstance()->getStringForKey(std::string(chartext));
	auto item_name = LabelTTF::create(strText, "Arial", 25);
	item_name->setTag(444);
	item_name->setAnchorPoint(Point::ZERO);
	item_name->setPosition(140, 40);
	item->addChild(item_name);

	return item;
}
