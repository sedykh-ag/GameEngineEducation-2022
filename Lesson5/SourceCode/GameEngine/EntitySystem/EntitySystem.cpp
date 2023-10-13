#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "ScriptProxy.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler)
{
	ecs.entity("inputHandler")
		.set(InputHandlerPtr{ inputHandler });
	ecs.entity("renderEngine")
		.set(RenderEnginePtr{ renderEngine });


	register_ecs_mesh_systems(ecs);
	register_ecs_control_systems(ecs);
	register_ecs_phys_systems(ecs);

	auto cubeControl = ecs.entity()
		.set(Position{ 0.f, 0.f, 0.f })
		.set(Velocity{ 0.f, 0.f, 0.f })
		.set(Speed{ 10.f })
		.set(FrictionAmount{ 0.9f })
		.set(JumpSpeed{ 10.f })
		.set(Gravity{ 0.f, -9.8065f, 0.f })
		.set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
		.set(Bounciness{ 0.3f })
		.set(CScriptProxy("movable.lua"))
		//.add<Controllable>()
		.add<CubeMesh>();

	auto cubeMoving = ecs.entity()
		.set(Position{ 0.f, 0.f, 0.f })
		.set(Velocity{ 0.f, 3.f, 0.f })
		.set(Gravity{ 0.f, -9.8065f, 0.f })
		.set(BouncePlane{ 0.f, 1.f, 0.f, 5.f })
		.set(Bounciness{ 1.f })
		.add<CubeMesh>();

}

void EntitySystem::Update()
{
		ecs.progress();
}