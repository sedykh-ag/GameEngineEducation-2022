#include "GameObject.h"

void GameObject::SetPosition(vec3 p)
{
	m_vPosition[0] = p.x();
	m_vPosition[1] = p.y();
	m_vPosition[2] = p.z();

	m_pRenderProxy->SetPosition(m_vPosition);
}

vec3 GameObject::GetPosition()
{
	return vec3(m_vPosition[0], m_vPosition[1], m_vPosition[2]);
}