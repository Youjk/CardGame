#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
	技能学院Layer
*/
class ColleageLayer :
	public Layer
{
public:
	ColleageLayer(void);
	~ColleageLayer(void);

	CREATE_FUNC(ColleageLayer);
	bool init();

private:
	void initframe(); //初始化背景UI
	void initcard(); //初始化卡牌UI
	void inittext(); //初始化文字
	void menu_help_callback(Ref* pSender); //帮助按钮回调
	void menu_reset_callback(Ref* pSender); //重置按钮回调
	void menu_learn_callback(Ref* pSender); //学习按钮回调

private:
	MenuItemSprite* reset_Item;
	MenuItemSprite* learn_Item;
	LabelTTF* origin_skill;
	LabelTTF* origin_skill_describe;
	LabelTTF* new_skill;
	LabelTTF* new_skill_describe;
	LabelTTF* none_describe;
	Sprite* magic;
	Sprite* book;
};

