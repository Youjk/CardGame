#pragma once
#include "cocos2d.h"

USING_NS_CC;

//’Ω∂∑Ω·À„Layer
class BattleResultLayer :
	public Layer
{
public:
	BattleResultLayer(void);
	~BattleResultLayer(void);

	bool init();
	CREATE_FUNC(BattleResultLayer);

	void InitBk();

	void showResult();
	void changeProgress(float dt);
	void changescore(float dt);
	void showcard(float dt);
	
	void initListener();

private:
	ProgressTimer* level_progress;
	LabelTTF* br_coin_value;
	LabelTTF* br_exp_value;
	EventListenerTouchOneByOne* listener;

	int m_coin;
	int m_exp;

	bool m_isTouchEnable;
};

