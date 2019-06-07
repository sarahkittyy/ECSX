#pragma once

#include <unordered_map>
#include <vector>

#include "ECSX/Common.hpp"
#include "ECSX/Component.hpp"
#include "ECSX/Entity.hpp"
#include "ECSX/System.hpp"

namespace ECSX
{

/**
 * @brief The main entity-storing world.
 * 
 */
class World
{
public:
	/**
	 * @brief Construct the world.
	 * 
	 */
	World();

	/**
	 * @brief Destroy the world.
	 * 
	 */
	virtual ~World();

	/**
	 * @brief Create a new entity in the world.
	 * 
	 * @return Entity* A pointer to the newly created entity.
	 */
	Entity* createEntity();

	/**
	 * @brief Remove an entity from the world.
	 * 
	 * @param id The ID of the entity to destroy.
	 */
	void destroyEntity(uuid_t id);

	/**
	 * @brief Get an entity given it's ID.
	 * 
	 * @param id The ID of the entity.
	 * @return Entity* A pointer to that entity.
	 */
	Entity* getEntity(uuid_t id);

	/**
	 * @brief Configure a system to run on this world.
	 * 
	 * @tparam Sys The system to run.
	 * @param args The arguments to pass to the system constructor.
	 * @returns System* A pointer to the created system.
	 */
	template <class Sys, class... Args>
	Sys* registerSystem(Args&&... args)
	{
		//Check to make sure the system doesn't exist already.
		for (auto& i : mSystems)
		{
			if (systemIsType<Sys>(&i))
			{
				//Return the system that already exists.
				return reinterpret_cast<Sys*>(i.get());
			}
		}

		// Create, configure, push, and return the system.
		std::shared_ptr<System> sys(new Sys(args...));
		mSystems.push_back(sys);

		sys->mEntities = &mEntities;
		configureSystem(sys);

		return reinterpret_cast<Sys*>(mSystems.back().get());
	}

	/**
	 * @brief Updates all systems.
	 * 
	 */
	void tick();

protected:
	/**
	 * @brief Derived world classes may have extra application globals they store. This can be inherited and used to pass pointers of these globals down to all system objects.
	 * 
	 * @param sys A system being registered.
	 */
	virtual void configureSystem(std::shared_ptr<System>& sys);

	/**
	 * @brief Called every tick().
	 * Can be inherited.
	 * 
	 */
	virtual void onTick();

private:
	/// A map of entity IDs to the entity object itself.
	std::unordered_map<uuid_t, Entity> mEntities;
	/// A vector of all registered systems.
	std::vector<std::shared_ptr<System>> mSystems;

	/**
	 * @returns true if the system can be downcasted to type `Sys`.
	 * 
	 */
	template <typename Sys>
	bool systemIsType(std::shared_ptr<System>* system)
	{
		return dynamic_cast<Sys*>(system->get()) != nullptr;
	}

	/// The next entity ID.
	uuid_t mNextID;
};

}