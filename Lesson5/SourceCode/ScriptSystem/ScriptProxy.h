#pragma once

#include "Common.h"
#include <sol/sol.hpp>

class SCRIPTSYSTEM_API CScriptProxy
{
public:
	CScriptProxy() = delete;
	CScriptProxy(const char* filename);

	template<typename T>
	void PassVariable(T var, const char* name);

	void Update(float dt);
private:
	sol::state lua_script;
};

