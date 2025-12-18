#include "Mage.h"
#include "Utils.h"
#include <iostream>
#include <stdexcept>

Mage::Mage(unsigned health, const char* name, const Position& pos, Weapon weapon, unsigned dmg, const char* ability, double coeff)
	:Player(health, name, pos, weapon, dmg)
{
	if (coeff < 0 || coeff > 1.0)
		throw std::invalid_argument("Coefficient must be between 0 and 1");

	this->coeff = coeff;
	this->ability = copyStr(ability);

}
Mage::Mage(const Mage& other) : Mage(other.health, other.name, other.pos, other.weapon, other.attack_damage, other.ability, other.coeff)
{
}

Mage& Mage::operator=(const Mage& other)
{
	if (this != &other)
	{
		Player::operator=(other);
		char* tempAbility = copyStr(other.ability);
		delete[] ability;
		ability = tempAbility;
		coeff = other.coeff;
	}

	return *this;
}
Mage::~Mage()
{
	delete[] ability;
}

void Mage::print() const
{
	Player::print();
	std::cout << ability << " " << coeff << "\n";
}
Player* Mage::clone() const
{
	return new Mage(*this);
}

void Mage::attack(Player& other)
{
	if (!canAttack(other))
		throw std::logic_error("Cannot attack this player");

	unsigned preAttack = coeff * other.getHealth();
	other.handleAttack(preAttack);

	if (!other.isDead())
		other.handleAttack(attack_damage);
}