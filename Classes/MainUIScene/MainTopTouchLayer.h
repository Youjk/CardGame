#pragma once
#include "cocos2d.h"

USING_NS_CC;
class MainTopTouchLayer :
	public Layer
{
public:
	MainTopTouchLayer(void);
	~MainTopTouchLayer(void);

	virtual bool init();
	CREATE_FUNC(MainTopTouchLayer);
	
	void InitSysInfo(); //��ʼ��UI

private:
	Node* sysInfo;
};

