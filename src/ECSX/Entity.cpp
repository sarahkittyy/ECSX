#include "ECSX/Entity.hpp"

namespace ECSX
{

Entity::Entity(uuid_t id)
	: mID(id)
{
}

uuid_t Entity::id()
{
	return mID;
}

}