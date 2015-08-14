#include "Archives.h"

Archives* Archives::m_pArchieves =NULL;

Archives::Archives(void)
{
}


Archives::~Archives(void)
{
}

Archives* Archives::getInstance()
{
	if (!m_pArchieves)
	{
		m_pArchieves = new Archives();
	}

	CCASSERT(m_pArchieves, "创建读取档类实例失败");

	return m_pArchieves;
}

bool Archives::isExist()
{
	if (!UserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml",  false))
	{
		return false;
	}

	return true;
}

//从存档中获取主角属性
void Archives::getHero_Property(Hero& var)
{
	var.setName(getHero_Name());
	var.setLevel(getHero_Level());
	var.setDiamond(getHero_Diamond());
	var.setExp(getHero_Exp());
	var.setCurLevelMaxExp(getHero_CurLevelMaxExp());
	var.setStrength(getHero_Strength());
	var.setMoney(getHero_Money());
	var.setLeaderShip(getHero_Leadership());
	var.setTeamLv(getHero_TeamLv());
	var.setRank(getHero_Rank());
}

//将主角属性写入存档
void Archives::setHero_Property(const Hero &var)
{
	UserDefault* udf = UserDefault::getInstance();
	udf->setStringForKey("Hero_Name", var.getName());
	udf->setIntegerForKey("Hero_Level", var.getLevel());
	udf->setIntegerForKey("Hero_Diamond", var.getDiamond());
	udf->setIntegerForKey("Hero_Exp",var.getExp());
	udf->setIntegerForKey("Hero_CurLevelMaxExp", var.getCurLevelMaxExp());
	udf->setIntegerForKey("Hero_Strength", var.getStrength());
	udf->setIntegerForKey("Hero_Money", var.getMoney());
	udf->setIntegerForKey("Hero_Leadership", var.getLeaderShip());
	udf->setIntegerForKey("Hero_TeamLv", var.getTeamLv());
	udf->setIntegerForKey("Hero_Rank", var.getRank());

	udf->flush();
}

void Archives::setHero_Name(std::string var)
{
	UserDefault::getInstance()->setStringForKey("Hero_Name", var);
	UserDefault::getInstance()->flush();
}

std::string Archives::getHero_Name()
{
	return UserDefault::getInstance()->getStringForKey("Hero_Name", "null");
}

void Archives::setHero_Level(int var)
{
	UserDefault::getInstance()->setIntegerForKey("Hero_Level", var);
	UserDefault::getInstance()->flush();
}

int Archives::getHero_Level()
{
	return UserDefault::getInstance()->getIntegerForKey("Hero_Level", 0);
}

void Archives::setHero_Diamond(int var)
{
	UserDefault::getInstance()->setIntegerForKey("Hero_Diamond", var);
	UserDefault::getInstance()->flush();
}

int Archives::getHero_Diamond()
{
	return UserDefault::getInstance()->getIntegerForKey("Hero_Diamond", 0);
}

void Archives::setHero_Exp(int var)
{
	UserDefault::getInstance()->setIntegerForKey("Hero_Exp", var);
	UserDefault::getInstance()->flush();
}

int Archives::getHero_Exp()
{
	return UserDefault::getInstance()->getIntegerForKey("Hero_Exp", 0);
}

void Archives::setHero_CurLevelMaxExp(int var)
{
	UserDefault::getInstance()->setIntegerForKey("Hero_CurLevelMaxExp", var);
	UserDefault::getInstance()->flush();
}

int Archives::getHero_CurLevelMaxExp()
{
	return UserDefault::getInstance()->getIntegerForKey("Hero_CurLevelMaxExp", 0);
}

void Archives::setHero_Strength(int var)
{
	UserDefault::getInstance()->setIntegerForKey("Hero_Strength", var);
	UserDefault::getInstance()->flush();
}

int Archives::getHero_Strength()
{
	return UserDefault::getInstance()->getIntegerForKey("Hero_Strength", 0);
}

void Archives::setHero_Money(int var)
{
	UserDefault::getInstance()->setIntegerForKey("Hero_Money", var);
	UserDefault::getInstance()->flush();
}

int Archives::getHero_Money()
{
	return UserDefault::getInstance()->getIntegerForKey("Hero_Money", 0);
}

void Archives::setHero_Leadership(int var)
{
	UserDefault::getInstance()->setIntegerForKey("Hero_Leadership", var);
	UserDefault::getInstance()->flush();
}

int Archives::getHero_Leadership()
{
	return UserDefault::getInstance()->getIntegerForKey("Hero_Leadership", 0);
}

void Archives::setHero_TeamLv(int var)
{
	UserDefault::getInstance()->setIntegerForKey("Hero_TeamLv", var);
	UserDefault::getInstance()->flush();
}

int Archives::getHero_TeamLv()
{
	return UserDefault::getInstance()->getIntegerForKey("Hero_TeamLv", 0);
}

void Archives::setHero_Rank(int var)
{
	UserDefault::getInstance()->setIntegerForKey("Hero_Rank", var);
	UserDefault::getInstance()->flush();
}

int Archives::getHero_Rank()
{
	return UserDefault::getInstance()->getIntegerForKey("Hero_Rank", 0);
}