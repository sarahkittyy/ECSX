#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "ECSX/Common.hpp"
#include "ECSX/Component.hpp"
#include "ECSX/Entity.hpp"

namespace ECSX
{

class World;

/**
 * @brief Generic ECS System class.
 * 
 */
class System
{
public:
	/**
	 * @brief Destroy the system
	 * 
	 */
	virtual ~System();

	/**
	 * @brief Update the system.
	 * 
	 */
	virtual void tick();

protected:
	/**
	 * @brief Returns a vector of entities,
	 * each with all components specified in the
	 * template parameter.
	 * 
	 * @tparam Components The components the entity must have.
	 * @return std::vector<Entity*> A vector of matching entities.
	 */
	template <typename... Components>
	std::vector<Entity*> each()
	{
		std::vector<Entity*> valid_entities;
		//Iterate over all entities...
		for (auto& [id, e] : *mEntities)
		{
			//If it has component types `Components...`,
			//use it.
			if (e.has<Components...>())
			{
				valid_entities.push_back(&e);
			}
		}
		//Return the valid entities.
		return valid_entities;
	}

	/**
	 * @brief Runs an action on every entity with all components specified
	 * in the template parameter.
	 * 
	 * @tparam Components The components to check.
	 * @param action The action to take on all valid matchin entities.
	 */
	template <typename... Components>
	void each(std::function<void(Entity*)> action)
	{
		//Iterate over all entities...
		for (auto& [id, e] : *mEntities)
		{
			//If it has component types `Components...`,
			//call action() with it.
			if (e.has<Components...>())
			{
				action(&e);
			}
		}
	}

	/**
	 * @brief Return a vector of all entities.
	 * 
	 * @return std::vector<Entity*> A vector of pointers to all entities.
	 */
	std::vector<Entity*> all();

	/**
	 * @brief Run an action on all entities.
	 * 
	 * @param action The action to run on each entity.
	 */
	void all(std::function<void(Entity*)> action);

private:
	friend class World;   /// For setting pointers upon system registration.

	/// Pointer to the world's map of entities.
	std::unordered_map<uuid_t, Entity>* mEntities;
};

}