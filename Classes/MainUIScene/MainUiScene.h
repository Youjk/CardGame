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

	//��ҳ��������ս�����̵ꡢ�罻�����ԵȰ�ť�ص�
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
	BattleResultLayer* _battleResultLayer; //ս������layer
	FightLayer* _fightLayer; //ս��ģ��
	StoreLayer* _storeLayer; //�̵�ģ��
	SocialLayer* _socialLayer; //�����б�
	MoreLayer* _moreLayer;//����
	LabelTTF* text;
	String pStrTemp; // ����ֵ
	

	void ConfigureMultiplexLayer();  //�ײ�tab�л�
	void ConfigureTopUI();           //��ʼ������һЩ״̬UI
	void ConfigureButtonUI();        //��ʼ���ײ�һЩ��ťUI
	void ConfigureTouchLayer();      //��ӵ�����ﵯ���Ĵ�����
	void ScrollText();

	void show_BattleResult(Ref* pSender);
	void update(float dt);
	void updatestrengthtime(float dt);

	std::string getstrengthTime(std::string strcurtime);
	std::string getstrengthValue(std::string strcurvalue);
};

