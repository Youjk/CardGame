#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
	����ѧԺLayer
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
	void initframe(); //��ʼ������UI
	void initcard(); //��ʼ������UI
	void inittext(); //��ʼ������
	void menu_help_callback(Ref* pSender); //������ť�ص�
	void menu_reset_callback(Ref* pSender); //���ð�ť�ص�
	void menu_learn_callback(Ref* pSender); //ѧϰ��ť�ص�

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

