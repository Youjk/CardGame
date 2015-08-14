#include "TaskListLayer.h"
#include "Dialog/DialogLayer.h"
#include "Utils/AppStringFile.h"


TaskListLayer::TaskListLayer(void)
{
}


TaskListLayer::~TaskListLayer(void)
{
}

bool TaskListLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();

	TableView* tableView = TableView::create(this, Size(600, 500));
	tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL); //方向垂直
	tableView->setPosition(Point::ZERO);
	tableView->setDelegate(this);
	tableView->setTag(0);
	addChild(tableView);

	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);  //填充次序从上到下
	tableView->reloadData();

	return true;
}

//定制每个cell的size
Size TaskListLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	log("tableCellSizeForIndex");
	return Size(556, 130);
}

//触摸到某个cell的事件
void TaskListLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
	int i = cell->getIdx();
	if (i < 3 && cell->getChildByTag(777)->getChildByTag(888))
	{
		DialogLayer* d = DialogLayer::create(Sprite::createWithSpriteFrameName("tipsbase.png"));
		d->setContentSize(Size(500, 200));
		//d->setPosition(0, -100);
		String* title = String::createWithFormat("task_get_text_%d", i + 1);
		d->setTitle(AppStringFile::getInstance()->getStringForKey(title->getCString()).c_str());
		d->addButton("ok", 
			Sprite::createWithSpriteFrameName("button_0.png"),
			Sprite::createWithSpriteFrameName("button_2.png"),
			Sprite::createWithSpriteFrameName("button_2.png"),
			[d](Ref* pSender){
				d->removeFromParent();
			},0);
		Director::getInstance()->getRunningScene()->addChild(d);
		cell->getChildByTag(777)->removeChildByTag(888);
	}
}


//定制每个cell的内容
TableViewCell* TaskListLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
	//'poreturn TableView::create()
	log("%d_tableCellAtIndex", idx);
	String* str = String::createWithFormat("yjk_%d", idx);
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

//确定这个tableview的cell行数
ssize_t  TaskListLayer::numberOfCellsInTableView(TableView *table)
{
	log("numberOfCellsInTableView");
	return 4;
}

//设置单元格高亮的状态
void TaskListLayer::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellHighlight");
	if (cell->getIdx() != 3 && cell->getChildByTag(777)->getChildByTag(888))
	{
		cell->getChildByTag(777)->getChildByTag(888)->setVisible(true);
	}
}

//设置单元格非高亮的状态
void TaskListLayer::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	log("tableCellUnhighlight");
	if (cell->getIdx() != 3 && cell->getChildByTag(777)->getChildByTag(888))
	{
		cell->getChildByTag(777)->getChildByTag(888)->setVisible(false);
	}
}

//由于TableView是继承ScrollView，所以要继承这两个方法
//滑动tableView触发
void TaskListLayer::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidScroll");
}

void TaskListLayer::scrollViewDidZoom(cocos2d::extension::ScrollView* view)
{
	log("scrollViewDidZoom");
}

Node* TaskListLayer::getItemNode(int i)
{
	auto item = Node::create();
	//Item背景
	auto item_bk = Sprite::create("ui/listbutton_base1.png");
	item_bk->setAnchorPoint(Point::ZERO);
	item_bk->setPosition(Vec2(20 , 0));
	item->addChild(item_bk);


	//变亮的背景，点击就设visible为true，否则为false
	auto item_hi = Sprite::createWithSpriteFrameName("listbutton_base1_1.png");
	item_hi->setScale(2.0f);
	item_hi->setTag(888);
	item_hi->setAnchorPoint(Point::ZERO);
	item_hi->setPosition(Vec2(20, 0));
	item->addChild(item_hi);

	if (i == 3)
	{
		item_hi->setVisible(false);
	}
	std::string item_image_frame_name, item_image_name, strtext_title_name,strtext_name,item_sign_name;

	item_sign_name = "sign_complete.png";
	if (i == 0)
	{
		item_image_frame_name = "littlecard_frame_class5.png";
		item_image_name = "icon_diamond1.png";
		strtext_title_name = "task_tittle_3";
		strtext_name = "task_text_3";
	}else if(i == 1)
	{
		item_image_frame_name = "littlecard_frame_class4.png";
		item_image_name = "icon_bigcoin.png";
		strtext_title_name = "task_tittle_2";
		strtext_name = "task_text_2";
	}else if(i == 2)
	{
		item_image_frame_name = "littlecard_frame_class4.png";
		item_image_name = "icon_salve.png";
		strtext_title_name = "task_tittle_1";
		strtext_name = "task_text_1";
	}else if(i == 3)
	{
		item_image_frame_name = "littlecard_frame_class5.png";
		item_image_name = "icon_diamond1.png";
		strtext_title_name = "task_tittle_0";
		strtext_name = "task_text_0";
		item_sign_name = "sign_underway.png";
	}

	//头像框
	auto  item_image_frame = Sprite::createWithSpriteFrameName(item_image_frame_name);
	item_image_frame->setAnchorPoint(Point::ZERO);
	item_image_frame->setPosition(30,15);
	item->addChild(item_image_frame);

	//头像
	auto item_image = Sprite::createWithSpriteFrameName(item_image_name);
	item_image->setAnchorPoint(Point::ZERO);
	item_image->setPosition(30, 15);
	item->addChild(item_image);

	//名字
	std::string strtext = AppStringFile::getInstance()->getStringForKey(strtext_title_name);
	auto item_title = LabelTTF::create(strtext, "Arial", 25);
	item_title->setAnchorPoint(Point::ZERO);
	item_title->setPosition(140, 75);
	item->addChild(item_title);

	strtext = AppStringFile::getInstance()->getStringForKey(strtext_name);
	auto item_text = LabelTTF::create(strtext, "Arial", 20);
	item_text->setAnchorPoint(Point::ZERO);
	item_text->setPosition(Vec2(140, 35));
	item->addChild(item_text);

	auto item_sign = Sprite::createWithSpriteFrameName(item_sign_name);
	item_sign->setTag(999);
	item_sign->setAnchorPoint(Point::ZERO);
	item_sign->setPosition(Vec2(430, 30));
	item->addChild(item_sign);

	return item;
}