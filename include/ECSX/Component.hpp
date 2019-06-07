#pragma once

#include "ECSX/Common.hpp"

namespace ECSX
{

/**
 * @brief Base component class for storing in entities.
 * 
 */
class Component
{
public:
	/**
	 * @brief To make this component a polymorphic type.
	 * 
	 */
	virtual ~Component();
};

}