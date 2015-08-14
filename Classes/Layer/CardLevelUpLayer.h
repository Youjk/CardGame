#pragma once
#include "cocos2d.h"

USING_NS_CC;
class CardLevelUpLayer :
	public Layer
{
public:
	CardLevelUpLayer(void);
	~CardLevelUpLayer(void);

	CREATE_FUNC(CardLevelUpLayer);
	bool init();

private:
	void initframe(); //初始化框背景
	void initcontent(); //初始化卡牌
	virtual void update(float delta);
	MenuItemSprite* createMenuItem(std::string spritename, std::string textname); //根据传入返回menuitem；
	void choose_food_menucalback(Ref* pSender);           //吞噬按钮回调函数
	void start_update_level_menucallback(Ref* pSender);   //开始升级按钮回调

private:
	Sprite* card_levelup_base;      //英雄升级框
	Sprite* card_levelup_pro_base;  //英雄升级框属性背景
	Sprite* left_eated_01_bk;  //左右三排人物框
	Sprite* left_eated_02_bk;
	Sprite* left_eated_03_bk;
	Sprite* right_eated_01_bk;
	Sprite* right_eated_02_bk;
	Sprite* right_eated_03_bk;
	Sprite* need_eat_pro_base; //花费值框

	MenuItemSprite* choose_food_Item; //吞噬按钮
	MenuItemSprite* startlevel_Item; //升级按钮

	Node* card;             //中间那个card
	Node* left_eat_card_01;
	Node* left_eat_card_02;
	Node* left_eat_card_03;
	Node* right_eat_card_01;
	Node* right_eat_card_02;
	Node* right_eat_card_03;

	Sprite* add[6];        //加号sprite
	LabelTTF* need_xp;
	LabelTTF* need_coin;
	LabelTTF* get_xp;

	Node* littlecard[6];  //需要被合成的6张卡牌
	Sprite* littlecard_flash_sprite[6];  //动画卡片
	ProgressTimer* level_progress;  //进度条
	Sprite* progress_fr;     //进度条frame
};

