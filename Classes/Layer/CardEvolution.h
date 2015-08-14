#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
	��������
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
	void start_evolve_menucallback(Ref* pSender); //��ť�ص�
	void before_card_sprite_disappear(); //��߿�����ʧ
	void after_card_show(); //�ұ߾Ͱ�ɫshan��������
	void show_choose_hero();


	Sprite* cardevolutionbase;    //����Ӣ�۽�����ı���
	MenuItemSprite* startevolve_Item; //������ť
	Sprite* equit_bk[5]; //װ��������

	Node* choose_card_before; //ѡ��Ӣ��ǰ
	Sprite* card_before;      //��߿���
	LayerColor* shadow;       //�ұ߿��Ƶ�����

	Node* weapon_evolve[5]; //װ����Ƭ

	LabelTTF* text_evolve_before[4] ; //��������
	LabelTTF* value_evolve_before[4]; //����ֵ

	LabelTTF* level_evolve_before;  //������������
	LabelTTF* life_evolve_before;
	LabelTTF* attack_evolve_before;
	LabelTTF* skill_evole_before;

	Sprite* weapon_evolve_animate_sprite[5];
	Sprite* before_card_animate_sprite;

	Sprite* shan;  //��ɫ��Ƭ���뵭��
	Sprite* kuang;
};

