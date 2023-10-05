#include "ecsMesh.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "RenderThread.h"
#include "RenderEngine.h"
#include "CubeRenderProxy.h"

void register_ecs_mesh_systems(flecs::world &ecs)
{
  static auto renderQuery = ecs.query<RenderEnginePtr>();
  ecs.system<const CubeMesh, const Position>()
    .each([&](flecs::entity e, const CubeMesh& cubeMesh, const Position& pos)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
          RenderProxy* renderProxy = new CubeRenderProxy;
          re.ptr->GetRT()->EnqueueCommand(RC_CreateCubeRenderObject, renderProxy);

          float position[3];
          position[0] = pos.x;
          position[1] = pos.y;
          position[2] = pos.z;

          renderProxy->SetPosition(position);

          e.set(RenderProxyPtr{ renderProxy });
          e.remove<CubeMesh>();
      });
    });

  ecs.system<RenderProxyPtr, const Position>()
    .each([&](RenderProxyPtr &renderProxy, const Position &pos)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
           float position[3];
           position[0] = pos.x;
           position[1] = pos.y;
           position[2] = pos.z;

           renderProxy.ptr->SetPosition(position);
      });
    });
}

