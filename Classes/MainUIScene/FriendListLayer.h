#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

/*
	�����б�
*/
class FriendListLayer :
	public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	FriendListLayer(void);
	~FriendListLayer(void);

	CREATE_FUNC(FriendListLayer);
	virtual bool init();

	//������ĳ��cell���¼�
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);

	//����ÿ��cell��size
	virtual Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);

	//����ÿ��cell������
	virtual TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);

	//ȷ�����tableview��cell����
	virtual ssize_t  numberOfCellsInTableView(TableView *table);

	//���õ�Ԫ�������״̬
	virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
	//���õ�Ԫ��Ǹ�����״̬
	virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);

	//����TableView�Ǽ̳�ScrollView������Ҫ�̳�����������������ʱ�����
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);

	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);

private:
	void slideValueChanged(Ref* sender, Control::EventType type);
	Node* getItemNode(int i);

private:
	bool m_bTable;            
	bool m_bSlider;
	Size size;      //��Ļ��С
	TableView* tableView;       //tableView
	ControlSlider* slider;     //������
};

