/*
 * This example is simple and demonstrates the basic usage of
 * components and systems.
 */

#include <iostream>
#include <string>
#include "ECSX/ECSX.hpp"

/**
 * @brief A simple name component.
 * 
 */
struct Name : public ECSX::Component
{
	Name(std::string name = "unnamed")
		: name(name)
	{
	}
	std::string name;
};

/**
 * @brief A position component.
 * 
 */
struct Position : public ECSX::Component
{
	Position(int x = 0, int y = 0)
		: x(x), y(y)
	{
	}
	int x, y;
};

/**
 * @brief Prints out the name and position of all entities with
 * both of those components.
 * 
 */
class NamedPositions : public ECSX::System
{
public:
	void tick()
	{
		//For every entity with a Position and Name component..
		each<Position, Name>([](ECSX::Entity* entity) {
			Position* p = entity->get<Position>();
			Name* n		= entity->get<Name>();
			std::cout << n->name << " is at position "
					  << p->x << ", " << p->y << "\n";
		});
	}
};

/**
 * @brief Moves all entities in the X direction by 1 every tick.
 * 
 */
class MoveX : public ECSX::System
{
public:
	void tick()
	{
		each<Position>([](ECSX::Entity* entity) {
			Position* p = entity->get<Position>();
			p->x++;
		});
	}
};

int main()
{
	ECSX::World world;
	// Create an entity
	ECSX::Entity* entity = world.createEntity();
	// Give it a name and a position component.
	entity->use<Position>(10, 10);
	entity->use<Name>("MyEntity!");
	//Register the two systems.
	world.registerSystem<MoveX>();
	world.registerSystem<NamedPositions>();

	//Tick the world a few times.
	world.tick();
	world.tick();
	world.tick();
}