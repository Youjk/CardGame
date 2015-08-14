#pragma once
#include "cocos2d.h"

USING_NS_CC;

class LoginScene :
	public Layer
{
public:
	LoginScene(void);
	~LoginScene(void);
	CREATE_FUNC(LoginScene);
	static Scene* createScene();

private:
	virtual bool init();
	void initUI();
	void initWebView();
	void startGameMenuCallback(Ref* pSender);
};

