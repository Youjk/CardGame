#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
*  Ӣ�۽���
*/
class MyCardLayer :
	public Layer
{
public:
	MyCardLayer(void);
	~MyCardLayer(void);
	virtual bool init();
	CREATE_FUNC(MyCardLayer);

private:
	void initframe();  //���ر߿򱳾�
	void initList();   //����Ӣ���б�
};

