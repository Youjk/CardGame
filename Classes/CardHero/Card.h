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
	int m_level;    //�ȼ�
	int m_attack;	//������
	int m_defence;	//������
	TeamPostion m_teamPos;   //�Ŷ���λ�� 
};

