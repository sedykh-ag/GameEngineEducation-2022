#include <fstream>

#include "ScriptProxy.h"
#include "InputHandler.h"

CScriptProxy::CScriptProxy()
{
    std::ifstream file("../../../Assets/scripts/movable.lua");
    std::stringstream buffer;
    buffer << file.rdbuf();
    const std::string lua_code = buffer.str();

    InputHandler* inputHandler = new InputHandler();

    lua_script.new_usertype<InputHandler>("InputHandler",
        "TestLeftRight", &InputHandler::TestLeftRight);

    lua_script["inputHandler"] = inputHandler;
    lua_script.script(lua_code.c_str());
}

void CScriptProxy::PassFloat(const float& var, const char* name)
{
    lua_script[name] = var;
}

float CScriptProxy::GetFloat(const char* name)
{
    return lua_script[name];
}


void CScriptProxy::Update(float dt)
{
    lua_script["Update"](dt);
}