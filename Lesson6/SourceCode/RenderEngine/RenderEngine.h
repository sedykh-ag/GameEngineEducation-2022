#pragma once

#include <vector>

#include "Common.h"
#include "RenderObject.h"
#include "RenderProxy.h"
#include "DefaultGeometry/CubeRenderObject.h"

class RenderThread;
class IRenderBackend;

class RENDERENGINE_API RenderEngine
{
	friend class RenderThread;

public:
	RenderEngine() = delete;
	RenderEngine(HINSTANCE hInstance);
	RenderEngine(const RenderEngine& renderEngine) = delete;
	~RenderEngine();

	void Update();

	RenderThread* const GetRT();

private:
	void Init();
	void CreateCubeRenderObject(RenderProxy* renderProxy);

	HWND InitMainWindow(HINSTANCE hInstance);
	HWND m_hwnd = nullptr;

	long m_Width = 800;
	long m_Height = 600;

	RenderThread* m_pRT;
	IRenderBackend* m_pRenderBackend;

	std::vector<RenderObject*> m_renderObjects;
};
