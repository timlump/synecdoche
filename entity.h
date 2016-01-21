#include <vector>
#include <glm/glm.hpp>
#include <lua.hpp>

class Entity
{
public:
	Entity();
	~Entity();
	virtual void update();
	virtual void interact();
	Entity *mParent;
	std::vector<Entity*> mChildren;
	glm::mat4 mTransform;
	static void bindToLua(lua_State *L);
};