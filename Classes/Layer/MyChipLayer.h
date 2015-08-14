#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MyChipLayer :
	public Layer
{
public:
	MyChipLayer(void);
	~MyChipLayer(void);
	CREATE_FUNC(MyChipLayer);
	bool init();

private:
	void initframe();
	void initList();
};

