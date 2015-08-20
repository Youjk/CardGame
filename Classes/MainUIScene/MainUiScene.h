#pragma once
#include "cocos2d.h"
#include "MainUIScene/MainUILayer.h"
#include "MainUIScene/InstanceLayer.h"
#include "BattleScene/BattleResultLayer.h"
#include "BattleScene/FightLayer.h"
#include "MainUIScene/StoreLayer.h"
#include "MainUIScene/SocialLayer.h"
#include "MainUIScene/MoreLayer.h"

USING_NS_CC;

#define  MAIN_TOP						1
#define	 MAIN_TOP_STRENGTH_TIME			2
#define  MAIN_TOP_STRENGTH_VALUE        3
#define  MAIN_TOP_STRENGTH_PROGRESS     4

class MainUiScene :
	public Layer
{
public:
	MainUiScene(void);
	~MainUiScene(void);

	static Scene* createScene();
	CREATE_FUNC(MainUiScene);

	virtual bool init();

	//主页、副本、战斗、商店、社交、攻略等按钮回调
	void button_Homepage(Ref* pSender);
	void button_Instance(Ref* pSender);
	void button_Fight(Ref* pSender);
	void button_Store(Ref* pSender);
	void button_Social(Ref* pSender);
	void button_More(Ref* pSender);

private:
	MainUILayer* _mainUILayer;    
	InstanceLayer* _instanceUILayer;
	LayerMultiplex* _mutiplexLayer;
	BattleResultLayer* _battleResultLayer; //战斗结算layer
	FightLayer* _fightLayer; //战斗模块
	StoreLayer* _storeLayer; //商店模块
	SocialLayer* _socialLayer; //好友列表
	MoreLayer* _moreLayer;//攻略
	LabelTTF* text;
	String pStrTemp; // 体力值
	

	void ConfigureMultiplexLayer();  //底部tab切换
	void ConfigureTopUI();           //初始化顶部一些状态UI
	void ConfigureButtonUI();        //初始化底部一些按钮UI
	void ConfigureTouchLayer();      //添加点击人物弹出的触摸层
	void ScrollText();

	void show_BattleResult(Ref* pSender);
	void update(float dt);
	void updatestrengthtime(float dt);

	std::string getstrengthTime(std::string strcurtime);
	std::string getstrengthValue(std::string strcurvalue);
};

