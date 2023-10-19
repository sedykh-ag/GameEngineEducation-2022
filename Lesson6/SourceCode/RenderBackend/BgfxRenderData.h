#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "IRenderData.h"

class RenderObject;

class RENDERBACKEND_API BgfxRenderData final : public IRenderData
{
public:
	BgfxRenderData(
		void* vertices, UINT32 verticesSize,
		void* indices, UINT32 indicesSize,
		std::string vsShaderName, std::string psShaderName);

	bgfx::VertexBufferHandle GetVertexBuffer() { return m_vbh; }
	bgfx::IndexBufferHandle GetIndexBuffer() { return m_ibh; }
	bgfx::ProgramHandle GetProgramHandle() { return m_ProgramHandle; }
	virtual void GetPosition(float* result) override;
	virtual void SetPosition(float position[3]) override;

private:
	bgfx::VertexLayout m_Layout = bgfx::VertexLayout();
	bgfx::VertexBufferHandle m_vbh = bgfx::VertexBufferHandle();
	bgfx::IndexBufferHandle m_ibh = bgfx::IndexBufferHandle();
	bgfx::ProgramHandle m_ProgramHandle = bgfx::ProgramHandle();

	float m_vPosition[3];
};

