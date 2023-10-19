#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "ScriptProxy.h"

#include <sol/sol.hpp>
#include "../xml/tinyxml2.h"

void EntitySystem::EntitiesFromXML(const char* filepath)
{
    // load xml
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filepath);

    tinyxml2::XMLElement* pRoot = doc.RootElement();
    if (pRoot != nullptr)
    {
        for (
            tinyxml2::XMLElement* pEntity = pRoot->FirstChildElement("Entity");
            pEntity != nullptr;
            pEntity = pEntity->NextSiblingElement("Entity")
            )
        {
            auto entity = ecs.entity();
            // position
            tinyxml2::XMLElement* pPosition = pEntity->FirstChildElement("Position");
            if (pPosition != nullptr)
            {
                float x, y, z;
                x = pPosition->FirstChildElement("x")->FloatText();
                y = pPosition->FirstChildElement("y")->FloatText();
                z = pPosition->FirstChildElement("z")->FloatText();
                entity.set(Position{ x, y, z });
            }
            // velocity
            tinyxml2::XMLElement* pVelocity = pEntity->FirstChildElement("Velocity");
            if (pVelocity != nullptr)
            {
                float x, y, z;
                x = pVelocity->FirstChildElement("x")->FloatText();
                y = pVelocity->FirstChildElement("y")->FloatText();
                z = pVelocity->FirstChildElement("z")->FloatText();
                entity.set(Velocity{ x, y, z });
            }
            // speed
            tinyxml2::XMLElement* pSpeed = pEntity->FirstChildElement("Speed");
            if (pSpeed != nullptr)
            {
                float val;
                val = pSpeed->FloatText();
                entity.set(Speed{ val });
            }
            // friction amount
            tinyxml2::XMLElement* pFrictionAmount = pEntity->FirstChildElement("FrictionAmount");
            if (pFrictionAmount != nullptr)
            {
                float val;
                val = pFrictionAmount->FloatText();
                entity.set(FrictionAmount{ val });
            }
            // jump speed
            tinyxml2::XMLElement* pJumpSpeed = pEntity->FirstChildElement("JumpSpeed");
            if (pJumpSpeed != nullptr)
            {
                float val;
                val = pJumpSpeed->FloatText();
                entity.set(JumpSpeed{ val });
            }
            // gravity
            tinyxml2::XMLElement* pGravity = pEntity->FirstChildElement("Gravity");
            if (pGravity != nullptr)
            {
                float x, y, z;
                x = pGravity->FirstChildElement("x")->FloatText();
                y = pGravity->FirstChildElement("y")->FloatText();
                z = pGravity->FirstChildElement("z")->FloatText();
                entity.set(Gravity{ x, y, z });
            }
            // bounce plane
            tinyxml2::XMLElement* pBouncePlane = pEntity->FirstChildElement("BouncePlane");
            if (pBouncePlane != nullptr)
            {
                float x, y, z, w;
                x = pBouncePlane->FirstChildElement("x")->FloatText();
                y = pBouncePlane->FirstChildElement("y")->FloatText();
                z = pBouncePlane->FirstChildElement("z")->FloatText();
                w = pBouncePlane->FirstChildElement("w")->FloatText();
                entity.set(BouncePlane{ x, y, z, w });
            }
            // bounciness
            tinyxml2::XMLElement* pBounciness = pEntity->FirstChildElement("Bounciness");
            if (pBounciness != nullptr)
            {
                float val;
                val = pBounciness->FloatText();
                entity.set(Bounciness{ val });
            }
            // controllable (through inputhandler system)
            tinyxml2::XMLElement* pControllable = pEntity->FirstChildElement("Controllable");
            if (pControllable != nullptr)
            {
                entity.add<Controllable>();
            }
            // CScriptProxy (through script system)
            tinyxml2::XMLElement* pCScriptProxy = pEntity->FirstChildElement("CScriptProxy");
            if (pCScriptProxy != nullptr)
            {
                entity.add<CScriptProxy>();
            }
            // CubeMesh
            tinyxml2::XMLElement* pCubeMesh = pEntity->FirstChildElement("CubeMesh");
            if (pCubeMesh != nullptr)
            {
                entity.add<CubeMesh>();
            }
        }
    }

}

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);

    /*
    auto cubeControl = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 0.f, 0.f })
        .set(Speed{ 10.f })
        .set(FrictionAmount{ 0.9f })
        .set(JumpSpeed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
        .set(Bounciness{ 0.3f })
        .add<Controllable>()
        .add<CubeMesh>();
    */

    EntitiesFromXML("./xml/cubeControl.xml"); // load from XML
    
    // load via old way (loading from XML also works fine)
    auto cubeScripted = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 3.f, 0.f })
        .set(Speed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 5.f })
        .set(Bounciness{ 0.3f })
        .set(CScriptProxy())
        .add<CubeMesh>();
    // EntitiesFromXML("./xml/cubeScripted.xml");
    
}

void EntitySystem::Update()
{
    ecs.progress();
}