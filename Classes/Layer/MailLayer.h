#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MailLayer :
	public Layer
{
public:
	MailLayer(void);
	~MailLayer(void);

	CREATE_FUNC(MailLayer);
	bool init();

private:
	void initframe();
};

