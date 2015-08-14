#pragma once
#include "cocos2d.h"
#include "Layer/MailLayer.h"
#include "Layer/CardLevelUpLayer.h"
#include "Layer/MyCardLayer.h"
#include "Layer/TaskLayer.h"
#include "Layer/ColleageLayer.h"
#include "Layer/MyChipLayer.h"
#include "Layer/CardEvolution.h"

USING_NS_CC;

enum MainUI_CurUI
{
	MAIN_UI,
	CARD_UI,
	SALE_UI,
	EVOLVE_UI,
	LEVEL_IP_UI,
	TASK_UI,
	COLLEAGE_UI,
	MAIL_UI,
	CHIP_UI
};

class MainUILayer :
	public Layer
{
public:
	MainUILayer(void);
	~MainUILayer(void);

	CREATE_FUNC(MainUILayer);
	bool init();
	void restoreToMainUI();

private:
	void return_callback(Ref* pSender);
	void configureTeamUI();   //显示TeamUI
	void configureMenuUI();   //显示菜单UI
	void menu_mail_callback(Ref* pSender); //邮箱menu回调函数
	void showMailUI();  //显示邮箱界面
	void showCardUI();  //显示英雄界面
	void showCardEvolveUI();  //显示进化界面
	void showChipUI();    //显示碎片界面
	void showCardLevelupUI();  //显示卡牌升级界面
	void showColleageUI();      //显示技能学院界面
	void showTaskUI();      //显示奖励界面
	void textlevel_flash(float dt);  //文字闪烁
	MenuItemSprite* createMenuItem(std::string spritename, std::string textname);  //根据名字和位置创建menuItem
	void removeMainUI();  //移除teamUI和menuUI，准备切换到下一场景

private:
	MainUI_CurUI m_curUI; //当前是哪个UI界面
	MailLayer* _mailLayer; //邮箱界面 
	CardLevelUpLayer* _cardLevelUpLayer;  //升级界面
	MyCardLayer* _cardLayer; //英雄页面
	TaskLayer* _taskLayer; //奖励界面
	ColleageLayer* _colleageLayer; // 技能学院界面
	MyChipLayer* _chipLayer; //碎片界面
	CardEvolution* _cardEvolution; //进化界面
	Sprite* team;    //队伍UI
	Node* menu;      //菜单UI
	Sprite* text_max[5];   //五个角色下面max文本
	Node* text_level[5];   
};

