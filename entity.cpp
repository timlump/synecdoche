#include "entity.h"
#include <lua.hpp>

Entity::Entity()
{
	mParent = NULL;
	mTransform = glm::mat4(1.0f);
}

Entity::~Entity()
{
	
}

void Entity::update()
{
	
}

void Entity::interact()
{
	
}

void Entity::bindToLua(lua_State *L)
{
	
}