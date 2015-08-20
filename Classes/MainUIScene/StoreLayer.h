#pragma once
#include "cocos2d.h"
#include "Dialog/DialogLayer.h"

USING_NS_CC;

class StoreLayer : public Layer
{
public:
	StoreLayer(void);
	~StoreLayer(void);
	CREATE_FUNC(StoreLayer);
	virtual bool init();

private:
	void initFrame();
	void initTitle();
	void initMenu();
	MenuItemSprite* createMenuItem(std::string textname); //创建按钮
	void createDialog(std::string titlename); //创建对话框

private:
	Node* menu;

};

