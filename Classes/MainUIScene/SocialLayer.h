#pragma once
#include "cocos2d.h"

USING_NS_CC;

class SocialLayer :
	public Layer
{
public:
	SocialLayer(void);
	~SocialLayer(void);

	CREATE_FUNC(SocialLayer);
	bool init();

private:
	void initframe();
	void initTitle();
	void initList();

};

