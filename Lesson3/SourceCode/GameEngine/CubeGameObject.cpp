#include "CubeGameObject.h"
#include "../RenderEngine/CubeRenderProxy.h"

CubeGameObject::CubeGameObject()
{
	m_pRenderProxy = new CubeRenderProxy();
}

void CubeJumping::UpdateDeltaTime(float dt)
{
	vec3 p = GetPosition();
	
	if (p.y() < 0.001f) {
		vel = vec3(0.0f, 5.0f, 0.0f);
	}
	
	p += vel * dt;
	SetPosition(p);

	vel += vec3(0.0f, -g * dt, 0.0f);
}

void CubeMoving::UpdateTotalTime(float t, float dt)
{
	vec3 p = GetPosition();
	vel = vec3(0.0f, 0.0f, 2.0*sin(5.0*t));
	p += vel * dt;
	SetPosition(p);
}

void CubeControlled::UpdateAction(EInputCommand action, float dt)
{
	vec3 p = GetPosition();
	
	vel = vec3(0.0f, 0.0f, 0.0f);

	if (action == eIC_GoLeft)
		vel += vec3(5.0f, 0.0f, 0.0f);
	if (action == eIC_GoRight)
		vel += vec3(-5.0f, 0.0f, 0.0f);


	p += vel * dt;
	SetPosition(p);
}