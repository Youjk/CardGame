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
	MenuItemSprite* createMenuItem(std::string textname); //������ť
	void createDialog(std::string titlename); //�����Ի���

private:
	Node* menu;

};

