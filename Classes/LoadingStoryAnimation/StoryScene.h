#pragma once
#include "cocos2d.h"

USING_NS_CC;

class StoryScene :
	public Layer
{
public:
	StoryScene(void);
	~StoryScene(void);
	CREATE_FUNC(StoryScene);

	static Scene* createScene();
	virtual bool init();
	virtual void update(float delta);

private:
	Sprite* backgroud1;  //����ɳĮ�󱳾�
	Sprite* story_scene_xing;  //����ͼƬ

	Sprite* backgroud2;  //����2
	Sprite* huodui;      //���

	Sprite* play_mt;
	Sprite* play_dede;
	Sprite* play_shaman;

	Sprite* background3;
	Sprite* zhangpenghuo;
	Sprite* boom1_1;          //��ը
	Sprite* boom1_2;
	Sprite* boom2_1;
	Sprite* boom2_2;

	void pass_story(Ref* pSedenr);

	void begin_scene1();
	void end_scene1(float dt);
	void begin_scene2();
	void end_sence2(float dt);
	void begin_scene3();
	void end_sence3(float dt);

	void shakeHead(Sprite*& sprite);   //˵��ʱ���ﶶ��

	//��ʾ�Ի�
	void showText(const char* pszName, float delaytime = 1.0f, Point initposition = Point(20, 80),Point moveposition = Point(0, 80), bool isDisapper = true);
	
	//��ʾ����Ի�
	void showTextBox(const char* pszName, Point position);
	//������˸
	void xingFlash();

	void showLines();  //��ʾ����
	void showBoom_1(); //��ʾ��ը
};

