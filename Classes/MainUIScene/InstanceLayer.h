#pragma once
#include "cocos2d.h"
#include "MainUIScene/NormalInstanceListLayer.h"

#define INSTANCE_UI 0
#define LINEUP_UI 1

USING_NS_CC;

class InstanceLayer :
	public Layer
{
public:
	InstanceLayer(void);
	~InstanceLayer(void);
	CREATE_FUNC(InstanceLayer);
	bool init();
	void call_by_main(); //���ظ�����ҳ��
	void return_instance();
	void return_lineup(Ref* pSender);

private:
	void initframe();
	void initList();
	void initTitle();

private:
	int m_curUI;  //��ǰ�����ĸ�ҳ��
	NormalInstanceListLayer* normalInstanceListLayer;
	Menu* menu_right;
	Menu* menu_left;   //��߾�Ӣ��ť
	Menu* menu_left_new;
	Sprite* title_custom_instance; //��������
	Sprite* title_custom_lineup;

	Node* lineup_content;
	Sprite* listbase; //�м䱳��

	int m_pos_x[6];
	int m_pos_y[6];
};

