#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "ecsWeapon.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler)
{
    ecs.entity("inputHandler")
      .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
      .set(RenderEnginePtr{ renderEngine });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);
    register_ecs_weapon_systems(ecs);

    auto target = ecs.entity()
      .add<CubeMesh>()
      .add<Target>()
      .set(Position{ 0.f, 0.f, 0.f })
      .set(Radius{ 1.0f });

    auto weapon = ecs.entity()
      .set(Position{ 0.f, 2.f, -5.f })
      .set(Direction{ 0.f, -1.f, 2.f })
      .set(Weapon{ 0.f, 0.1f, 5.0f, 6, 6 });
}

void EntitySystem::Update()
{
    ecs.progress();
}