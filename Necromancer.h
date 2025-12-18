#pragma once
#include "Mage.h"
#include "PlayerCollection.h"

class Necromancer : public Mage
{
public:
	Necromancer(unsigned health, const char* name, const Position& pos, Weapon weapon, unsigned dmg, const char* ability, double coeff);
	void attack(Player& other) override;

private:
	PlayerCollection coll;
};

