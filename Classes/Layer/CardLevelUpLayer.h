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
	void initframe(); //��ʼ���򱳾�
	void initcontent(); //��ʼ������
	virtual void update(float delta);
	MenuItemSprite* createMenuItem(std::string spritename, std::string textname); //���ݴ��뷵��menuitem��
	void choose_food_menucalback(Ref* pSender);           //���ɰ�ť�ص�����
	void start_update_level_menucallback(Ref* pSender);   //��ʼ������ť�ص�

private:
	Sprite* card_levelup_base;      //Ӣ��������
	Sprite* card_levelup_pro_base;  //Ӣ�����������Ա���
	Sprite* left_eated_01_bk;  //�������������
	Sprite* left_eated_02_bk;
	Sprite* left_eated_03_bk;
	Sprite* right_eated_01_bk;
	Sprite* right_eated_02_bk;
	Sprite* right_eated_03_bk;
	Sprite* need_eat_pro_base; //����ֵ��

	MenuItemSprite* choose_food_Item; //���ɰ�ť
	MenuItemSprite* startlevel_Item; //������ť

	Node* card;             //�м��Ǹ�card
	Node* left_eat_card_01;
	Node* left_eat_card_02;
	Node* left_eat_card_03;
	Node* right_eat_card_01;
	Node* right_eat_card_02;
	Node* right_eat_card_03;

	Sprite* add[6];        //�Ӻ�sprite
	LabelTTF* need_xp;
	LabelTTF* need_coin;
	LabelTTF* get_xp;

	Node* littlecard[6];  //��Ҫ���ϳɵ�6�ſ���
	Sprite* littlecard_flash_sprite[6];  //������Ƭ
	ProgressTimer* level_progress;  //������
	Sprite* progress_fr;     //������frame
};

