#include <lua.hpp>
#include <map>
#include <iostream>

namespace Snd
{
	class Sound
	{
		public:
			Sound(std::map<char,char*> args);
	};
	
	inline void bindToLua(lua_State *L)
	{
		std::cout << "*Binding SND module to LUA" << std::endl;
	}
}