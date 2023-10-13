#include "ScriptProxy.h"
#include "InputHandler.h"
#include <fstream>

CScriptProxy::CScriptProxy(const char* filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    const std::string lua_code = buffer.str();

    InputHandler* inputHandler = new InputHandler();

    lua_script.new_usertype<InputHandler>("InputHandler",
        "GetInputState", &InputHandler::GetInputState);

    lua_script.new_usertype<std::bitset<eIC_Max>>("Input",
        "test", &std::bitset<eIC_Max>::test);

    lua_script["inputHandler"] = inputHandler;
    lua_script["eIC_GoLeft"] = eIC_GoLeft;
    lua_script["eIC_GoRight"] = eIC_GoRight;

    lua_script.script(lua_code.c_str());
}

template<typename T>
void CScriptProxy::PassVariable(T var, const char* name)
{
    lua_script[name] = var;
}

void CScriptProxy::Update(float dt)
{
    lua_script["Update"](dt);
}