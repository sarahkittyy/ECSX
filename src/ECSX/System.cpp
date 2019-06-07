#include "ECSX/System.hpp"

namespace ECSX
{

System::~System()
{
}

void System::tick()
{
}

std::vector<Entity*> System::all()
{
	std::vector<Entity*> entities;
	//For every entity
	for (auto& [id, e] : *mEntities)
	{
		//Append it
		entities.push_back(&e);
	}

	//Return all entities
	return entities;
}

void System::all(std::function<void(Entity*)> action)
{
	//For every entity..
	for (auto& [id, e] : *mEntities)
	{
		//Call action() on it.
		action(&e);
	}
}

}