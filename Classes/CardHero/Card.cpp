#include "Card.h"


Card::Card(void)
{
}


Card::~Card(void)
{
	if (this->m_sprite != nullptr)
	{
		this->m_sprite->release();
	}
}

void Card::bindSprite(Sprite* sprite)
{
	this->m_sprite = sprite;
	sprite->retain();
}

Sprite* Card::getSprite()
{
	return m_sprite;
}