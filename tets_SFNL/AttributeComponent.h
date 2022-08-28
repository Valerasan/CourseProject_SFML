#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H


class AttributeComponent
{
public:
	int hp;
	int hpMax;


	AttributeComponent(int HP);
	virtual ~AttributeComponent();

	//Functions
	void loseHP();
	void gainHP();
	const bool isDead() const;

};


#endif
