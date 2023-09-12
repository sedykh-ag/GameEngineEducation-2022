#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "Common.h"

namespace
{
	struct PosColorVertex
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_abgr;
	};
};

class RENDERENGINE_API RenderObject
{
public:
	RenderObject() = default;

	bgfx::VertexBufferHandle GetVertexBuffer() { return m_vbh; }
	bgfx::IndexBufferHandle GetIndexBuffer() { return m_ibh; }
	bgfx::ProgramHandle GetProgramHandle() { return m_ProgramHandle; }

protected:
	bgfx::VertexLayout m_Layout = bgfx::VertexLayout();
	bgfx::VertexBufferHandle m_vbh = bgfx::VertexBufferHandle();
	bgfx::IndexBufferHandle m_ibh = bgfx::IndexBufferHandle();
	bgfx::ProgramHandle m_ProgramHandle = bgfx::ProgramHandle();
};

