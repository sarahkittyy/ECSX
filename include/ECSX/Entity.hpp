#pragma once

#include <memory>
#include <vector>

#include "ECSX/Common.hpp"
#include "ECSX/Component.hpp"

namespace ECSX
{
/// For setting world as a friend class
class World;

/**
 * @brief The main entity object, stored in ECSX worlds.
 * Stores it's own components, with methods for component retrieval.
 * 
 */
class Entity
{
public:
	/**
	 * @brief Construct the entity.
	 * 
	 * @param id The ID of the entity.
	 * 
	 * @remarks Called by World::createEntity();
	 */
	Entity(uuid_t id);

	/**
	 * @brief Use a component on the entity.
	 * 
	 * @tparam Comp The component to use.
	 * @param args The arguments to pass to the component constructor. 
	 * @returns Comp* The created component.
	 */
	template <class Comp, class... Args>
	Comp* use(Args&&... args)
	{
		//Check to make sure the component isn't already in use.
		if (!has<Comp>())
		{
			//Push the component.
			mComponents.push_back(std::make_unique<Comp>(args...));
		}
		//Return the component.
		return get<Comp>();
	}

	/**
	 * @brief Checks if the entity has all of the given components.
	 * 
	 * @tparam Comps The components to check.
	 * @return true True if the entity has them all.
	 * @return false otherwise.
	 */
	template <class CompA, class CompB, class... Comps>
	bool has()
	{
		return has<CompA>() && has<CompB, Comps...>();
	}

	/**
	 * @brief Checks if this entity has a given component.
	 * 
	 * @tparam Comp The component to check for.
	 * @return true If the entity has it.
	 * @return false Otherwise.
	 */
	template <class Comp>
	bool has()
	{
		//Iterate over all components, and if any match, return true.
		for (auto& i : mComponents)
		{
			if (componentIsType<Comp>(&i))
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief Get a component from this entity.
	 * 
	 * @tparam Comp The component type to get.
	 * @return Comp* A pointer to that component, or nullptr if it doesn't exist.
	 */
	template <class Comp>
	Comp* get()
	{
		//Search for the component.
		for (auto& i : mComponents)
		{
			if (componentIsType<Comp>(&i))
			{
				return dynamic_cast<Comp*>(i.get());
			}
		}
		return nullptr;
	}

	/**
	 * @brief The entity's ID.
	 * 
	 */
	uuid_t id();

private:
	/// So world can configure the entity on creation
	friend class World;

	/// @brief The components attached to the entity.
	std::vector<std::unique_ptr<Component>> mComponents;

	/**
	 * @brief Checks if the given base component pointer
	 * can be downcasted to type `Derived`.
	 * 
	 * @tparam Derived The type to check.
	 * @param comp The component to check.
	 * @return true If comp can be casted into Derived.
	 * @return false Otherwise.
	 */
	template <typename Derived>
	bool componentIsType(std::unique_ptr<Component>* comp)
	{
		return dynamic_cast<Derived*>(comp->get()) != nullptr;
	}

	/// The entity ID as set by the world on construction.
	uuid_t mID;
};

}