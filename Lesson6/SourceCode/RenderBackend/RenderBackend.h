#include "IRenderBackend.h"

class RENDERBACKEND_API RenderBackend final : public IRenderBackend
{
public:
	virtual void Init() override;
	virtual void SetWindowHandle(void* windowHandle) override;
	virtual void SetViewTransform() override;
	virtual void Draw(IRenderData* renderObject) override;
	virtual void DrawFrame() override;

	virtual IRenderData* CreateRenderObject(
		void* vertices, UINT32 verticesSize,
		void* indices, UINT32 indicesSize,
		std::string vsShaderName, std::string psShaderName) override;

private:
	void* m_windowHandle;
};