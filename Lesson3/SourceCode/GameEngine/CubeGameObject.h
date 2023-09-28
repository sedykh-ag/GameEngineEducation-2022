#pragma once

#include "GameObject.h"
#include "Input.h"

class CubeGameObject : public GameObject
{
public:
	CubeGameObject();
	virtual void UpdateDeltaTime(float dt) {};
	virtual void UpdateTotalTime(float t, float dt) {};
	virtual void UpdateAction(EInputCommand action, float dt) {};

	vec3 vel = vec3(0.0f, 0.0f, 0.0f);
	const float g = 9.8f;
private:
};

class CubeJumping final : public CubeGameObject
{
	virtual void UpdateDeltaTime(float dt) override;
};

class CubeControlled final : public CubeGameObject
{
	virtual void UpdateAction(EInputCommand action, float dt) override;
};

class CubeMoving final : public CubeGameObject
{
	virtual void UpdateTotalTime(float t, float dt) override;
};