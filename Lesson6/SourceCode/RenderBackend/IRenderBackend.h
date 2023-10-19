#pragma once

#include "Common.h"
#include "IRenderData.h"

class RENDERBACKEND_API IRenderBackend
{
public:
	virtual void Init() = 0;
	virtual void SetWindowHandle(void* windowHandle) = 0;
	virtual void SetViewTransform() = 0;
	virtual void Draw(IRenderData* renderObject) = 0;
	virtual void DrawFrame() = 0;

	virtual IRenderData* CreateRenderObject(
		void* vertices, UINT32 verticesSize,
		void* indices, UINT32 indicesSize,
		std::string vsShaderName, std::string psShaderName
		) = 0;
};