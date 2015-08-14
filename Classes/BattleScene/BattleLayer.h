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
	void InitBk(); //��ʼ��������icon
	void InitContent(); //��ʼ������
	void InitSkillAnimation(); //��ʼ������
	void InitListener(); //��ʼ�������¼�

	void first_play(float dt); //���ŵڵ�һĻ����
	void second_play(float dt); //���ŵڶ�Ļ����
	void third_play(float dt); //���ŵ���Ļ����
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

	void show_hero_skill(int pos, const char* skill_name, const char* skill_spritename); ////�ĸ�λ�õ�Ӣ��ʹ��ʲôsprite��ʲô����
	void show_hero_skill_normal(int pos, int type, int dst);//�ĸ�λ��Ӣ��ʹ��ʲô����,�����ĸ�����
	void show_hit_skill(int pos, const char* skill_name, const char* skill_spritename); //��ʾ���ﱻ����Ч��
	void show_hit_value(int pos); //��ʾ�����ֵ
	void show_blood_value(int pos); //Ѫ������
	void monster_die(int pos); //������������
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
	Sprite* bk_1; //ѭ���������� bk1_bk_2
	Sprite* bk_2;
	Sprite* bk_3; 
	Sprite* gohead; //���ϵļ�ͷ
	Node* hero[6]; //�Լ��Ŀ���
	Node* monster[6]; //���˵Ŀ���

	int m_pos_hero_x[6];  //���Ƶ�λ��
	int m_pos_hero_y[6];
	int m_pos_monster_x[7];
	int m_pos_monster_y[7];

	Sprite* speed[3]; //���½�X1 X2 X3
	int m_curSpeed;  //��ǰ���±����ĸ�

	bool m_isShowGoAhead;
	int m_curPlay;       //��ǰ����

	Node* victory;
};

