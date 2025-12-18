#pragma once
#include "Player.h"

class Mage : public Player
{
public:
	Mage(unsigned health, const char* name, const Position& pos, Weapon weapon, unsigned dmg, const char* ability, double coeff);
	Mage(const Mage& other);
	Mage& operator=(const Mage& other);
	~Mage();

	void print() const override;
	Player* clone() const override;

	void attack(Player& other) override;
private:
	char* ability;
	double coeff;
};

