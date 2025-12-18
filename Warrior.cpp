#include "Warrior.h"
#include <iostream>
#include <fstream>

Warrior::Warrior(unsigned health, const char* name, const Position& pos, Weapon weapon, unsigned dmg, unsigned armor)
	: Player(health, name, pos, weapon, dmg), armor(armor) {}

void Warrior::handleAttack(unsigned dmg)
{
	if (armor >= dmg) {
		armor -= dmg;
	}
	else
	{
		unsigned actualDmg = dmg - armor;
		armor = 0;
		if (health >= actualDmg)
		{
			health -= actualDmg;
		}
		else
		{
			health = 0;
		}
	}
	
}
void Warrior::print() const
{
	Player::print();
	std::cout << armor << '\n';
}

Player* Warrior::clone() const
{
	return new Warrior(*this);
 }

void Warrior::serialize(std::ofstream& ofs) const 
{
	if (!ofs)
		throw std::invalid_argument("Invalid stream");


	ofs.write(reinterpret_cast<const char*>(&health), sizeof(health));
	size_t nameLen = strlen(name);
	ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
	ofs.write(name, nameLen);
	ofs.write(reinterpret_cast<const char*>(&pos), sizeof(pos));
	ofs.write(reinterpret_cast<const char*>(&weapon), sizeof(weapon));
	ofs.write(reinterpret_cast<const char*>(&attack_damage), sizeof(attack_damage));
	ofs.write(reinterpret_cast<const char*>(&armor), sizeof(armor));
}

void Warrior::deserialize(std::ifstream& ifs)
{
	if (!ifs)
		throw std::invalid_argument("Invalid stream");

	ifs.read(reinterpret_cast<char*>(&health), sizeof(health));
	size_t nameLen = 0;
	ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));

	delete[] name;
	this->name = new char[nameLen + 1];
	ifs.read(name, nameLen);
	this->name[nameLen] = '\0';

	ifs.read(reinterpret_cast<char*>(&pos), sizeof(pos));
	ifs.read(reinterpret_cast<char*>(&weapon), sizeof(weapon));
	ifs.read(reinterpret_cast<char*>(&attack_damage), sizeof(attack_damage));
	ifs.read(reinterpret_cast<char*>(&armor), sizeof(armor));
}