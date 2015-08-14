#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define  SPEED_X1 0
#define  SPEED_X2 1
#define  SPEED_X3 2

#define  FIRST 1
#define  SECOND 2
#define  THIRD 3

class BattleLayer :
	public Layer
{
public:
	BattleLayer(void);
	~BattleLayer(void);

	CREATE_FUNC(BattleLayer);
	static Scene* createScene();
	bool init();

private:
	void initframe();
	void InitBk(); //初始化背景及icon
	void InitContent(); //初始化卡牌
	void InitSkillAnimation(); //初始化动画
	void InitListener(); //初始化监听事件

	void first_play(float dt); //播放第第一幕画面
	void second_play(float dt); //播放第二幕画面
	void third_play(float dt); //播放第三幕画面
	void first_play_0(float dt);
	void first_play_1(float dt);
	void first_play_2(float dt);
	void first_play_3(float dt);
	void first_play_4(float dt);
	void first_play_5(float dt);
	void second_play_0(float dt);
	void second_play_1(float dt);
	void second_play_2(float dt);
	void second_play_3(float dt);
	void second_play_4(float dt);
	void second_play_5(float dt);
	void third_play_0(float dt);
	void third_play_1(float dt);
	void third_play_2(float dt);
	void third_play_3(float dt);
	void third_play_4(float dt);
	void third_play_5(float dt);

	void show_hero_skill(int pos, const char* skill_name, const char* skill_spritename); ////哪个位置的英雄使用什么sprite用什么技能
	void show_hero_skill_normal(int pos, int type, int dst);//哪个位置英雄使用什么技能,攻击哪个敌人
	void show_hit_skill(int pos, const char* skill_name, const char* skill_spritename); //显示怪物被消灭效果
	void show_hit_value(int pos); //显示被打击值
	void show_blood_value(int pos); //血量动画
	void monster_die(int pos); //敌人死亡动画
	void show_box(float dt);

	void show_GoAhead(float dt);
	void showallmonster();

	void showVictory(float dt);
	void showResult(float dt);
	void showText(float dt);

	void runcardshake();
	void runBk1(float dt);
	void runBk2(float dt);

private:
	Sprite* bk_1; //循环滚动背景 bk1_bk_2
	Sprite* bk_2;
	Sprite* bk_3; 
	Sprite* gohead; //向上的箭头
	Node* hero[6]; //自己的卡牌
	Node* monster[6]; //敌人的卡牌

	int m_pos_hero_x[6];  //卡牌的位置
	int m_pos_hero_y[6];
	int m_pos_monster_x[7];
	int m_pos_monster_y[7];

	Sprite* speed[3]; //坐下角X1 X2 X3
	int m_curSpeed;  //当前左下表是哪个

	bool m_isShowGoAhead;
	int m_curPlay;       //当前画面

	Node* victory;
};

