#pragma once
#include "cocos2d.h"

USING_NS_CC;

class FightLayer :
	public Layer
{
public:
	FightLayer(void);
	~FightLayer(void);

	bool init();
	CREATE_FUNC(FightLayer);
private:
	void initFrame();
	void initTitle();
	void initContent();
	void initInfo();

private:
	int m_times;
	int m_hp_time;
	int m_atktimes;

	LabelTTF* emb_hp;
	LabelTTF* emb_atk;
	LabelTTF* emb_time;

	MenuItemSprite* emb_hp_Item;
	MenuItemSprite* emb_atk_Item;
};

