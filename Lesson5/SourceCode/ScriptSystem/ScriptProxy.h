#pragma once

#include "Common.h"
#include <sol/sol.hpp>


class SCRIPTSYSTEM_API CScriptProxy
{
public:
	CScriptProxy();
	CScriptProxy(const char* filename) = delete; // does not work with ECS for some reason

	void PassFloat(const float& var, const char* name);
	float GetFloat(const char* name);

	void Update(float dt);

private:
	sol::state lua_script;
};

