#pragma once
#include "PLayer.h"

class Warrior : public Player
{
public:
	Warrior(unsigned health, const char* name, const Position& pos, Weapon weapon, unsigned dmg, unsigned armor);

	void handleAttack(unsigned dmg) override;
	void print() const override;
	Player* clone() const override;

	void serialize(std::ofstream& ofs) const override;
	void deserialize(std::ifstream& ifs) override;
private:
	unsigned armor;
};

