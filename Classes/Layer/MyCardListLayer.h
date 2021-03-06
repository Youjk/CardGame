#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Utils/AppStringFile.h"

USING_NS_CC;
USING_NS_CC_EXT;

static std::string spritename[14] = {
	"icon_occupation_warrior_button.png",
	"icon_occupation_shaman_button.png",
	"icon_occupation_rogue_button.png",
	"icon_occupation_hunter_button.png",
	"icon_occupation_druid_button.png",
	"icon_occupation_mage_button.png",
	"icon_occupation_priest_button.png",
	"icon_occupation_warlock_button.png",
	"icon_occupation_hunter_button.png",
	"icon_occupation_paladin_button.png",
	"icon_occupation_warrior_button.png",
	"icon_occupation_mage_button.png",
	"icon_occupation_warrior_button.png",
	"icon_occupation_mage_button.png",
};

/*
*  英雄ListView + sliding 界面
*/
class MyCardListLayer :
	public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	MyCardListLayer(void);
	~MyCardListLayer(void);

	CREATE_FUNC(MyCardListLayer);
	virtual bool init();

	//触摸到某个cell的事件
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);

	//定制每个cell的size
	virtual Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);

	//定制每个cell的内容
	virtual TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);

	//确定这个tableview的cell行数
	virtual ssize_t  numberOfCellsInTableView(TableView *table);

	//设置单元格高亮的状态
	virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
	//设置单元格非高亮的状态
	virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);

	//由于TableView是继承ScrollView，所以要继承这两个方法，滚动时候调用
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);

	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);

private:
	void slideValueChanged(Ref* sender, Control::EventType type);
	Node* getItemNode(int i);

private:
	bool m_bTable;            
	bool m_bSlider;
	Size size;      //屏幕大小
	TableView* tableView;       //tableView
	ControlSlider* slider;     //滑动条
};

