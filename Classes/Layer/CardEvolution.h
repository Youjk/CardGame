#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
	进化界面
*/
class CardEvolution :
	public Layer
{
public:
	CardEvolution(void);
	~CardEvolution(void);

	CREATE_FUNC(CardEvolution);
	bool init();

private:
	void initframe();
	void initcontent();
	void start_evolve_menucallback(Ref* pSender); //按钮回调
	void before_card_sprite_disappear(); //左边卡牌消失
	void after_card_show(); //右边就白色shan淡出淡入
	void show_choose_hero();


	Sprite* cardevolutionbase;    //两个英雄进化框的背景
	MenuItemSprite* startevolve_Item; //进化按钮
	Sprite* equit_bk[5]; //装备背景框

	Node* choose_card_before; //选择英雄前
	Sprite* card_before;      //左边卡牌
	LayerColor* shadow;       //右边卡牌的遮罩

	Node* weapon_evolve[5]; //装备卡片

	LabelTTF* text_evolve_before[4] ; //属性名字
	LabelTTF* value_evolve_before[4]; //属性值

	LabelTTF* level_evolve_before;  //卡牌下面文字
	LabelTTF* life_evolve_before;
	LabelTTF* attack_evolve_before;
	LabelTTF* skill_evole_before;

	Sprite* weapon_evolve_animate_sprite[5];
	Sprite* before_card_animate_sprite;

	Sprite* shan;  //白色卡片淡入淡出
	Sprite* kuang;
};

