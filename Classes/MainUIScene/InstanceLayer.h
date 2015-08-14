#pragma once
#include "cocos2d.h"
#include "MainUIScene/NormalInstanceListLayer.h"

#define INSTANCE_UI 0
#define LINEUP_UI 1

USING_NS_CC;

class InstanceLayer :
	public Layer
{
public:
	InstanceLayer(void);
	~InstanceLayer(void);
	CREATE_FUNC(InstanceLayer);
	bool init();
	void call_by_main(); //返回副本主页面
	void return_instance();
	void return_lineup(Ref* pSender);

private:
	void initframe();
	void initList();
	void initTitle();

private:
	int m_curUI;  //当前处于哪个页面
	NormalInstanceListLayer* normalInstanceListLayer;
	Menu* menu_right;
	Menu* menu_left;   //左边精英按钮
	Menu* menu_left_new;
	Sprite* title_custom_instance; //顶部文字
	Sprite* title_custom_lineup;

	Node* lineup_content;
	Sprite* listbase; //中间背景

	int m_pos_x[6];
	int m_pos_y[6];
};

