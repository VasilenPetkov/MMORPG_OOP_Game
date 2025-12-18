#include "PlayerCollection.h"

void PlayerCollection::resize()
{
	capacity *= 2;
	Player** temp = new Player * [capacity];

	for (size_t i = 0; i < size; i++)
	{
		temp[i] = players[i];
	}

	delete[] players;
	players = temp;
} 

void  PlayerCollection::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete players[i];
	}

	delete[] players;
}

PlayerCollection::PlayerCollection() : size(0), capacity(4)
{
	players = new Player * [capacity];
}
PlayerCollection::PlayerCollection(const PlayerCollection& other) : size(other.size), capacity(other.capacity)
{
	this->players = new Player * [capacity];

	try
	{
		for (size_t i = 0; i < size; i++)
		{
			this->players[i] = other.players[i]->clone();
		}
	}
	catch (std::exception& e)
	{
		free();
		throw;
	}
}
PlayerCollection& PlayerCollection::operator=(const PlayerCollection& other)
{
	if (this != &other)
	{
		free();
		this->size = other.size;
		this->capacity = other.capacity;
		this->players = new Player * [capacity];

		try
		{
			for (size_t i = 0; i < size; i++)
			{
				this->players[i] = other.players[i]->clone();
			}
		}
		catch (std::exception& e)
		{
			free();
			throw;
		}
	}

	return *this;
}
PlayerCollection::~PlayerCollection()
{
	free();
}

void  PlayerCollection::addPlayer(const Player& other)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(this->players[i]->getName(), other.getName()) == 0)
			throw std::invalid_argument("Player with such name is already in the collection");
	}

	if (size == capacity)
		resize();


	players[size++] = other.clone();
}

const Player* PlayerCollection::operator[](size_t index) const
{

	if (index >= size)
		throw std::invalid_argument("Invalid index");

	return players[index];
}
size_t  PlayerCollection::getCount() const
{
	return size;
} 

void  PlayerCollection::removePlayer(const char* name)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(players[i]->getName(), name) == 0)
		{
			delete players[i];
			for (int index = i; index < size - 1; index++)
			{
				players[index] = players[index + 1];
			}
			players[size - 1] = nullptr;
			--size;
			return;
		}
	}

	throw std::invalid_argument("Player not found");
}