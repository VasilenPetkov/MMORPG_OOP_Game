#include "Player.h"
#include "Utils.h"
#include <iostream>

Player::Player(unsigned health, const char* name, const Position& pos, Weapon weapon, unsigned dmg)
	:name(nullptr), health(health), pos(pos), weapon(weapon), attack_damage(dmg)
{
	if (dmg == 0)
		throw std::invalid_argument("Damage must be positive");

		this->name = copyStr(name);
	
}

Player::Player(const Player& other) : Player(other.health, other.name, other.pos, other.weapon, other.attack_damage)
{
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		char* newName = copyStr(other.name);
		delete[] this->name;
		this->name = newName;
		this->health = other.health;
		this->pos = other.pos;
		this->weapon = other.weapon;
		this->attack_damage = other.attack_damage;
	}

	return *this;
}


Player::~Player()
{
	delete[] this->name;
}

void Player::move(const Position& other)
{
	this->pos = other;
}
void Player::handleAttack(unsigned dmg)
{
	if (health < dmg)
	{
		health = 0;
	}
	else
	{
		health -= dmg;
	}
}
void Player::attack( Player& other)
{
	if (!canAttack(other))
		throw std::logic_error("Cannot attack this player");
		other.handleAttack(this->attack_damage);
}

bool Player::canAttack(const Player& other)
{
	if (other.isDead() || !this->pos.isAdjacent(other.pos))
		return false;

	return true;
}

unsigned Player::getAttackPower() const
{
	return attack_damage;
}

void Player::print() const
{
	std::cout << name << " " << health << attack_damage << '\n';
}

bool Player::isDead() const
{
	return health == 0;
}