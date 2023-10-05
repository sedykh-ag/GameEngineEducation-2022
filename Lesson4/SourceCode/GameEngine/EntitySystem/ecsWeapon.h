#pragma once
#include "flecs.h"
#include "ecsPhys.h"

void register_ecs_weapon_systems(flecs::world& ecs);

struct Weapon
{
  float timeToShoot;
  float timeBetweenShots;
  float timeReload;
  unsigned int shotsCapacity;
  unsigned int shotsLeft;
};

struct ShouldDestroy
{
  float timeLeft;
};

struct Bullet { };

struct Target { };

struct CheckFloorCollision { };

struct Direction
{
	float x, y, z;
};