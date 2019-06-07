/*
 * This file demonstrates how to inherit the ECSX::World class to include game/application globals
 * and pass them to systems.
 */

#include <iostream>
#include "ECSX/ECSX.hpp"

/**
 * @brief A derived base system to use for all future systems.
 * 
 */
class MySystem : public ECSX::System
{
public:
	virtual ~MySystem()
	{
	}

	// A pointer to the integer in MyWorld
	int* appVariable;
};

class MyWorld : public ECSX::World
{
public:
	MyWorld()
	{
		myVariable = 0;
	}
	void onTick()   //Called on every world.tick()!
	{
		myVariable++;
	}

protected:
	void configureSystem(std::shared_ptr<ECSX::System>& sys)
	{
		reinterpret_cast<MySystem*>(sys.get())->appVariable = &myVariable;
	}

private:
	// Our new global app variable.
	int myVariable;
};

struct BasicComponent : public ECSX::Component
{
	BasicComponent(int x)
		: variable(x)
	{
	}
	int variable;
};

/**
 * @brief Increments `variable` in `BasicComponent` by the new world global `myVariable` every tick.
 * 
 */
class BasicSystem : public MySystem
{
public:
	void tick()
	{
		each<BasicComponent>([this](ECSX::Entity* e) {
			int* x = &(e->get<BasicComponent>()->variable);
			*x += *appVariable;
			std::cout << "BasicComponent.variable is now " << *x << "\n";
		});
	}
};

int main()
{
	MyWorld world;
	ECSX::Entity* e = world.createEntity();
	e->use<BasicComponent>(0);
	world.registerSystem<BasicSystem>();

	world.tick();
	world.tick();
	world.tick();
	world.tick();
	world.tick();
}