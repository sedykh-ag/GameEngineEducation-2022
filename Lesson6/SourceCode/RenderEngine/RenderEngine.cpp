#include "RenderEngine.h"
#include "RenderThread.h"
#include "../RenderBackend/RenderBackend.h"

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

RenderEngine::RenderEngine(HINSTANCE hInstance)
{
	assert(!m_hwnd);
	m_hwnd = InitMainWindow(hInstance);
	assert(m_hwnd);

	m_pRenderBackend = new RenderBackend();
	m_pRenderBackend->SetWindowHandle(m_hwnd);

	m_pRT = new RenderThread(this);
}

void RenderEngine::Init()
{
	m_pRenderBackend->Init();
}

RenderEngine::~RenderEngine()
{
	DestroyWindow(m_hwnd);
}

HWND RenderEngine::InitMainWindow(HINSTANCE hInstance)
{
	std::wstring wstrWindowName = L"MainWnd";
	std::wstring wstrWindowCaption = L"GameEngine";

	HWND hwnd = nullptr;

	WNDCLASSEXW wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = wstrWindowName.c_str();
	wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return hwnd;
	}

	DWORD borderlessStyle = WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
	DWORD defaultStyle = WS_OVERLAPPEDWINDOW;

	RECT R = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&R, defaultStyle, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	hwnd = CreateWindow(wstrWindowName.c_str(), wstrWindowCaption.c_str(),
		defaultStyle, CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);
	if (!hwnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return hwnd;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return hwnd;
}

void RenderEngine::Update()
{
	m_pRenderBackend->SetViewTransform();

	for (auto* renderObject : m_renderObjects)
	{
		float position[3];
		renderObject->GetPosition(position);
		IRenderData* renderData = renderObject->GetRenderData();
		renderData->SetPosition(position);

		m_pRenderBackend->Draw(renderData);
	}

	m_pRenderBackend->DrawFrame();
}

void RenderEngine::CreateCubeRenderObject(RenderProxy* renderProxy)
{
	RenderObject* renderObject = new CubeRenderObject(renderProxy);

	IRenderData* renderData = m_pRenderBackend->CreateRenderObject(
		renderObject->GetVertices(), renderObject->GetVerticesSize(),
		renderObject->GetIndices(), renderObject->GetIndicesSize(),
		renderObject->GetVsShaderName(), renderObject->GetPsShaderName()
	);

	renderObject->SetRenderData(renderData);
	m_renderObjects.emplace_back(renderObject);
}

RenderThread* const RenderEngine::GetRT()
{
	return m_pRT;
}