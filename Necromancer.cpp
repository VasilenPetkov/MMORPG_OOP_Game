#include "Necromancer.h"
#include <stdexcept>

Necromancer::Necromancer(unsigned health, const char* name, const Position& pos, Weapon weapon, unsigned dmg, const char* ability, double coeff)
	:Mage(health, name, pos, weapon, dmg, ability, coeff) {}

void Necromancer::attack(Player& other)
{
	if(!canAttack(other))
		throw std::invalid_argument("Cannot attack this player");

	other.handleAttack(attack_damage);

	if (other.isDead())
	{
		coll.addPlayer(other);
		return;
	}

	
	unsigned randomIndex = std::rand() % coll.getCount();
	unsigned randomAttack = coll[randomIndex]->getAttackPower();

	other.handleAttack(randomAttack);

	if (other.isDead())
		coll.addPlayer(other);
}

