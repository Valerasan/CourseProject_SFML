#include "stdafx.h"
#include "AttributeComponent.h"


AttributeComponent::AttributeComponent(int HP)
	: hp(HP), hpMax(HP) {}

AttributeComponent::~AttributeComponent()
{
}



void AttributeComponent::loseHP()
{
	this->hp--;

	if (this->hp < 0)
		this->hp = 0;
}

void AttributeComponent::gainHP()
{
	this->hp++;
	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}




const bool AttributeComponent::isDead() const
{
	return this->hp <= 0;
}


