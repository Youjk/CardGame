
/*
	读取和写入xml中hero属性
*/

#pragma once

#include "cocos2d.h"
#include "CardHero/Hero.h"
#include <vector>

USING_NS_CC;
using std::vector;

class Archives
{
public:
	Archives(void);
	~Archives(void);

	static Archives* getInstance();
	bool isExist();

private:
	static Archives* m_pArchieves;

	class CGorbo
	{
	public:
		CGorbo();
		~CGorbo(){
			if (m_pArchieves != NULL)
			{
				delete m_pArchieves;
			}
		}

	private:
	};

	static CGorbo m_garbo;

public:
	void getHero_Property(Hero& var);
	void setHero_Property(const Hero &var);
	void setHero_Name(std::string);
	std::string getHero_Name();
	void setHero_Level(int var);
	int getHero_Level();
	void setHero_Diamond(int var);
	int getHero_Diamond();
	void setHero_Exp(int var);
	int getHero_Exp();
	void setHero_CurLevelMaxExp(int var);
	int getHero_CurLevelMaxExp();
	void setHero_Strength(int var);
	int getHero_Strength();
	void setHero_Money(int var);
	int getHero_Money();
	void setHero_Leadership(int var);
	int getHero_Leadership();
	void setHero_TeamLv(int var);
	int getHero_TeamLv();
	void setHero_Rank(int var);
	int getHero_Rank();
};

