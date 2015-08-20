#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
	�齱����
*/
class RaffleOneLayer :
	public Layer
{
public:
	RaffleOneLayer(void);
	~RaffleOneLayer(void);

	static Scene* createScene();
	CREATE_FUNC(RaffleOneLayer);

	virtual bool init();

	void initBK();

private:
	Node* animationNode;
	Sprite* raffle_daguang_flash; //�⶯���������Ǹ���ɫ��
	Sprite* raffle_guang; //��
	Node* chuizhiguang;  //��ֱ��Node
	Sprite* raffle_he_flash;
	Sprite* bai_xiangzi;
	Sprite* xiangzi_bottom;
	Sprite* xiangzi_top;
	Sprite* raffle_guangbai;
	LayerColor* white_layer;

private:
	void show_chuizhi_guang();
	void show_xiangzi();
	void show_card();
	void show_menu();
};

