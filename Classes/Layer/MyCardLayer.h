#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
*  英雄界面
*/
class MyCardLayer :
	public Layer
{
public:
	MyCardLayer(void);
	~MyCardLayer(void);
	virtual bool init();
	CREATE_FUNC(MyCardLayer);

private:
	void initframe();  //加载边框背景
	void initList();   //加载英雄列表
};

