#pragma once
#include "cocos2d.h"
#include "Layer/MailLayer.h"
#include "Layer/CardLevelUpLayer.h"
#include "Layer/MyCardLayer.h"
#include "Layer/TaskLayer.h"
#include "Layer/ColleageLayer.h"
#include "Layer/MyChipLayer.h"
#include "Layer/CardEvolution.h"

USING_NS_CC;

enum MainUI_CurUI
{
	MAIN_UI,
	CARD_UI,
	SALE_UI,
	EVOLVE_UI,
	LEVEL_IP_UI,
	TASK_UI,
	COLLEAGE_UI,
	MAIL_UI,
	CHIP_UI
};

class MainUILayer :
	public Layer
{
public:
	MainUILayer(void);
	~MainUILayer(void);

	CREATE_FUNC(MainUILayer);
	bool init();
	void restoreToMainUI();

private:
	void return_callback(Ref* pSender);
	void configureTeamUI();   //��ʾTeamUI
	void configureMenuUI();   //��ʾ�˵�UI
	void menu_mail_callback(Ref* pSender); //����menu�ص�����
	void showMailUI();  //��ʾ�������
	void showCardUI();  //��ʾӢ�۽���
	void showCardEvolveUI();  //��ʾ��������
	void showChipUI();    //��ʾ��Ƭ����
	void showCardLevelupUI();  //��ʾ������������
	void showColleageUI();      //��ʾ����ѧԺ����
	void showTaskUI();      //��ʾ��������
	void textlevel_flash(float dt);  //������˸
	MenuItemSprite* createMenuItem(std::string spritename, std::string textname);  //�������ֺ�λ�ô���menuItem
	void removeMainUI();  //�Ƴ�teamUI��menuUI��׼���л�����һ����

private:
	MainUI_CurUI m_curUI; //��ǰ���ĸ�UI����
	MailLayer* _mailLayer; //������� 
	CardLevelUpLayer* _cardLevelUpLayer;  //��������
	MyCardLayer* _cardLayer; //Ӣ��ҳ��
	TaskLayer* _taskLayer; //��������
	ColleageLayer* _colleageLayer; // ����ѧԺ����
	MyChipLayer* _chipLayer; //��Ƭ����
	CardEvolution* _cardEvolution; //��������
	Sprite* team;    //����UI
	Node* menu;      //�˵�UI
	Sprite* text_max[5];   //�����ɫ����max�ı�
	Node* text_level[5];   
};

