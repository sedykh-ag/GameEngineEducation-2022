#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "InputHandler.h"
#include "ScriptProxy.h"

void register_ecs_control_systems(flecs::world &ecs)
{
  static auto inputQuery = ecs.query<InputHandlerPtr>();

  ecs.system<Velocity, const Speed, const Controllable>()
    .each([&](flecs::entity e, Velocity &vel, const Speed &spd, const Controllable &)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        float deltaVel = 0.f;
        if (input.ptr->GetInputState().test(eIC_GoLeft))
          deltaVel -= spd;
        if (input.ptr->GetInputState().test(eIC_GoRight))
          deltaVel += spd;
        vel.x += deltaVel * e.delta_time();
      });
    });

  ecs.system<Velocity, const Speed, CScriptProxy>()
      .each([&](flecs::entity e, Velocity& vel, const Speed& spd, CScriptProxy& script)
        {
            script.PassFloat(vel.x, "vel_x");
            script.PassFloat(spd, "spd");

            script.Update(e.delta_time());

            vel.x = script.GetFloat("vel_x");
        }
  );

  ecs.system<const Position, Velocity, const Controllable, const BouncePlane, const JumpSpeed>()
    .each([&](const Position &pos, Velocity &vel, const Controllable &, const BouncePlane &plane, const JumpSpeed &jump)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane.x*pos.x + plane.y*pos.y + plane.z*pos.z < plane.w + planeEpsilon)
          if (input.ptr->GetInputState().test(eIC_Jump))
            vel.y = jump.val;
      });
    });
}

