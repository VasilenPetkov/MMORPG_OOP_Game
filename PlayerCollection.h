#pragma once
#include "PLayer.h"
class PlayerCollection
{
public:

	PlayerCollection();
	PlayerCollection(const PlayerCollection& other);
	PlayerCollection& operator=(const PlayerCollection& other);
	~PlayerCollection();

	void addPlayer(const Player& other);
	const Player* operator[](size_t index) const;
	size_t getCount() const;
	void removePlayer(const char* name);

private:
	Player** players;
	size_t size;
	size_t capacity;

	void resize();
	void free();
};

