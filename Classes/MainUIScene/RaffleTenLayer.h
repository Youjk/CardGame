#pragma once
#include "cocos2d.h"

USING_NS_CC;

class RaffleTenLayer :
	public Layer
{
public:
	RaffleTenLayer(void);
	~RaffleTenLayer(void);
	CREATE_FUNC(RaffleTenLayer);

	virtual bool init();

	void initBK();

	static Scene* createScene();

private:
	Node* animationNode;
	Sprite* raffle_daguang_flash; //光动画，地下那个白色光
	Sprite* raffle_guang; //光
	Node* chuizhiguang;  //垂直光Node
	Sprite* raffle_he_flash;
	Sprite* bai_xiangzi;
	Sprite* xiangzi_bottom;
	Sprite* xiangzi_top;
	Sprite* xiangzi_top_new;
	Sprite* raffle_guangbai;

	int m_cardth;
	int m_pos_x[10];
	int m_pos_y[10];

private:
	void show_chuizhi_guang();
	void show_xiangzi();
	void show_card();
	void show_menu();

	void show_box_card(float dt);
	void show_box_card_front(float dt);
};

