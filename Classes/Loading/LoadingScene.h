#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define TOTALNUMPICTURE 41   //�ܹ���Ҫ�����ص���Դ��

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
	void gotoNextScene(float dt);  //��ת����

	int _nNumberofLoaded;  //�Ѿ���������Դ��
	ProgressTimer* _loadProgress; //������
};

