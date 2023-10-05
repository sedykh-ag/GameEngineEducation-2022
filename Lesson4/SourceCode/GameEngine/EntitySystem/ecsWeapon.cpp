#include "ecsSystems.h"
#include "ecsWeapon.h"
#include "ecsControl.h"
#include "ecsMesh.h"
#include "../InputHandler.h"

void register_ecs_weapon_systems(flecs::world& ecs)
{
  static auto inputQuery = ecs.query<InputHandlerPtr>();

  // Bullet spawn on fire system
  ecs.system<const Position, const Direction, Weapon>()
    .each([&](flecs::entity e, const Position& pos, const Direction& dir, Weapon& wep)
    {
      wep.timeToShoot -= e.delta_time();
      if (wep.timeToShoot < 0.f)
      {
        inputQuery.each([&](InputHandlerPtr input)
          {
            if (input.ptr->GetInputState().test(eIC_Shoot))
            {
              e.world().entity()
                .set(Position{ pos })
                .set(Velocity{ dir.x, dir.y, dir.z })
                .set(Gravity{ 0.f, -9.8065f, 0.f })
                .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
                .set(Bounciness{ 0.2f })
                .set(Radius{ 1.0f })
                .add<Bullet>()
                .add<CubeMesh>()
                .add<CheckFloorCollision>();

              if (--wep.shotsLeft < 1)
              {
                wep.timeToShoot = wep.timeReload;
                wep.shotsLeft = wep.shotsCapacity;
              }
              else
                wep.timeToShoot = wep.timeBetweenShots;
            }
          });
      }
      });

  // Bullet collision-with-floor detection system
  ecs.system<const Position, const BouncePlane, const CheckFloorCollision>()
    .each([&](flecs::entity e, const Position& pos, const BouncePlane& plane, const CheckFloorCollision&)
    {
      float dotPos = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
      if (dotPos < plane.w)
      {
        e.set<ShouldDestroy>({ 5.f });
        e.remove<CheckFloorCollision>();
      }
    });

  // Self-destruction timer system
  ecs.system<ShouldDestroy, Position, RenderProxyPtr>()
    .each([&](flecs::entity e, ShouldDestroy& death, Position& pos, const RenderProxyPtr& proxy)
    {
      death.timeLeft -= e.delta_time();
      if (death.timeLeft < 0.f)
      {
        delete proxy.ptr;
        e.destruct();
      }
    });

  // All bullets query

  // Bullet-target (b-t) collision system
  
  ecs.system<Target, Position, Radius>()
    .each([&](flecs::entity t, const Target&, const Position& t_pos, const Radius& t_rad)
    {
      
      auto bulletsQuery = t.world().filter<Bullet, Position, Radius>();
      
      bulletsQuery.each([&](const Bullet&, const Position& b_pos, const Radius& b_rad)
      {
        float distSq = (t_pos.x - b_pos.x) * (t_pos.x - b_pos.x)
                     + (t_pos.y - b_pos.y) * (t_pos.y - b_pos.y)
                     + (t_pos.z - b_pos.z) * (t_pos.z - b_pos.z);

        float distCol = (t_rad.val + b_rad.val) * (t_rad.val + b_rad.val);

        if (distSq < distCol) 
        {
          t.remove<Target>();
          t.set<ShouldDestroy>({ 0.01f });
        }
      });
      

    });
    
    
  
}