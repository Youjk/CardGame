#include "CardHero/Hero.h"

Hero* Hero::m_pHero = NULL;

Hero::Hero(void)
{
}


Hero::~Hero(void)
{
}

Hero* Hero::getInstance()
{
	if (!m_pHero)
	{
		m_pHero = new Hero();
	}
	CCASSERT(m_pHero, "Hero����ʧ��");

	return m_pHero;
}