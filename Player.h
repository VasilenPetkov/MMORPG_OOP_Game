#pragma once
#include <stdexcept>
struct Position
{
	int x;
	int y;

	Position(int x, int y) : x(x), y(y) {}

	bool isAdjacent(const Position& other)
	{
		return std::abs(x - other.x) + std::abs(y - other.y) == 1;
	}
};

enum class Weapon
{
	Sword,
	Wand,
	Staff,
	Axe
};

class Player
{
public:
	Player(unsigned health, const char* name, const Position& pos, Weapon weapon, unsigned dmg);
	Player(const Player& other);
	Player& operator=(const Player& other);
	virtual ~Player();

	void move(const Position& other);
	virtual void handleAttack(unsigned dmg);
	virtual void attack( Player& other);
	bool canAttack(const Player& other);
	bool isDead() const;

	unsigned getAttackPower() const;
	const char* getName() const { return name; }
	unsigned getHealth() const { return health; }

	virtual void print() const;
	virtual Player* clone() const = 0;

	virtual void serialize(std::ofstream& ofs) const = 0;
	virtual void deserialize(std::ifstream& ifs) = 0;
protected:
	unsigned health;
	char* name;
	Position pos;
	Weapon weapon;
	unsigned attack_damage;
};

