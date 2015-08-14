#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define TOTALNUMPICTURE 41   //总共需要被加载的资源数

class LoadingScene :
	public Layer
{
public:
	LoadingScene(void);
	~LoadingScene(void);
	CREATE_FUNC(LoadingScene);

	static Scene* createScene();
	virtual bool init();

private:
	void initUI();
	void LoadPicResourceToCache();
	void LoadPicResourceCallBack(Texture2D *textture);
	void LoadHeroProperty();
	void gotoNextScene(float dt);  //跳转场景

	int _nNumberofLoaded;  //已经被加载资源数
	ProgressTimer* _loadProgress; //进度条
};

