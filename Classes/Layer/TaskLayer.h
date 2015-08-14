#pragma once
#include "cocos2d.h"

USING_NS_CC;

class TaskLayer :
	public Layer
{
public:
	TaskLayer(void);
	~TaskLayer(void);
	CREATE_FUNC(TaskLayer);

	virtual bool init();
private:
	void initframe();
};

