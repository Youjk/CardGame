#pragma once
#include "cocos2d.h"
#include <vector>
#include "CardHero/Card.h"

USING_NS_CC;
using std::vector;


class Hero
{
public:
	Hero(void);
	~Hero(void);
	static Hero* getInstance();

private:
	static Hero* m_pHero;

	class CGorbo
	{
	public:
		CGorbo();
		~CGorbo(){
			if (m_pHero != NULL)
			{
				delete m_pHero;
			}
		}

	private:
	};

	static CGorbo m_garbo;

	CC_SYNTHESIZE(std::string, m_Name, Name);
	CC_SYNTHESIZE(int, m_level, Level);
	CC_SYNTHESIZE(int, m_diamond, Diamond);
	CC_SYNTHESIZE(int, m_exp, Exp);
	CC_SYNTHESIZE(int, m_curLevelMaxExp, CurLevelMaxExp);
	CC_SYNTHESIZE(int, m_strength, Strength);
	CC_SYNTHESIZE(int, m_money, Money);
	CC_SYNTHESIZE(int, m_leadership, LeaderShip);
	CC_SYNTHESIZE(int, m_teamlv, TeamLv);
	CC_SYNTHESIZE(int, m_rank, Rank);

	CC_SYNTHESIZE(vector<Node*>, m_cards, Cards);
};

