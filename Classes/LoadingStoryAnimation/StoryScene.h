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
	Sprite* backgroud1;  //月亮沙漠大背景
	Sprite* story_scene_xing;  //星星图片

	Sprite* backgroud2;  //背景2
	Sprite* huodui;      //火堆

	Sprite* play_mt;
	Sprite* play_dede;
	Sprite* play_shaman;

	Sprite* background3;
	Sprite* zhangpenghuo;
	Sprite* boom1_1;          //爆炸
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

	void shakeHead(Sprite*& sprite);   //说话时人物抖动

	//显示对话
	void showText(const char* pszName, float delaytime = 1.0f, Point initposition = Point(20, 80),Point moveposition = Point(0, 80), bool isDisapper = true);
	
	//显示人物对话
	void showTextBox(const char* pszName, Point position);
	//星星闪烁
	void xingFlash();

	void showLines();  //显示光线
	void showBoom_1(); //显示爆炸
};

