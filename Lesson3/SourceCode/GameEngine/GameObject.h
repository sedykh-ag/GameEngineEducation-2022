#pragma once

#include "Common.h"
#include "RenderProxy.h"
#include "vec3.h"

class GameObject
{
public:
	GameObject() = default;

	~GameObject()
	{
		delete m_pRenderProxy;
	}

	void SetPosition(vec3 p);
	vec3 GetPosition();

	RenderProxy* const GetRenderProxy() { return m_pRenderProxy; }
protected:
	RenderProxy* m_pRenderProxy;

	float m_vPosition[3];
};

