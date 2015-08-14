#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum TeamPostion
{
	LeaderCard,
	MemberCard,
	NormalCard
};

class Card:public Node
{
public:
	Card(void);
	~Card(void);

	void bindSprite(Sprite* sprite);
	Sprite* getSprite();

private:
	Sprite* m_sprite;
	int m_level;    //等级
	int m_attack;	//攻击力
	int m_defence;	//防御力
	TeamPostion m_teamPos;   //团队中位置 
};

