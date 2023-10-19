#include "BgfxRenderData.h"
#include "Shaders/ShadersHelper.h"

BgfxRenderData::BgfxRenderData(
	void* vertices, UINT32 verticesSize,
	void* indices, UINT32 indicesSize,
	std::string vsShaderName, std::string psShaderName)
{
	m_Layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(vertices, verticesSize)
		, m_Layout
	);

	// Create static index buffer for triangle list rendering.
	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(indices, indicesSize)
	);

	m_ProgramHandle = ShadersHelper::LoadProgram(vsShaderName.c_str(), psShaderName.c_str());
}

void BgfxRenderData::SetPosition(float position[3])
{
	m_vPosition[0] = position[0];
	m_vPosition[1] = position[1];
	m_vPosition[2] = position[2];
}

void BgfxRenderData::GetPosition(float* result)
{
	result[0] = m_vPosition[0];
	result[1] = m_vPosition[1];
	result[2] = m_vPosition[2];
}