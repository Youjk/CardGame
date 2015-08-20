#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MoreLayer :
	public Layer
{
public:
	MoreLayer(void);
	~MoreLayer(void);

	CREATE_FUNC(MoreLayer);
	bool init();

private:
	void initframe();
	void initTitle();
	void initList();

};

