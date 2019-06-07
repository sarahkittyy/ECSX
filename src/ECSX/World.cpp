#include "ECSX/World.hpp"

namespace ECSX
{

World::World()
	: mNextID(0)
{
}

World::~World()
{
}

Entity* World::createEntity()
{
	//Create the entity.
	mEntities.emplace(std::piecewise_construct,
					  std::forward_as_tuple(mNextID),
					  std::forward_as_tuple(mNextID));

	//Increment for the next call.
	mNextID++;
	//Return a pointer to the entity.
	return &mEntities.at(mNextID - 1);
}

void World::destroyEntity(uuid_t id)
{
	//Remove the entity with ID `id` from the world.
	mEntities.erase(id);
}

Entity* World::getEntity(uuid_t id)
{
	//If we can't find it, return nullptr.
	if (mEntities.find(id) == mEntities.end())
	{
		return nullptr;
	}
	else
	{
		return &mEntities.at(id);
	}
}

void World::configureSystem(std::shared_ptr<System>& sys)
{
}

void World::tick()
{
	for (auto& sys : mSystems)
	{
		sys->tick();
	}
}

}