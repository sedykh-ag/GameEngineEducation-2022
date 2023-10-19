#include "RenderThread.h"
#include "RenderEngine.h"

template void RENDERENGINE_API RenderThread::EnqueueCommand<RenderProxy*>(ERenderCommand command, RenderProxy* renderProxy);

// Function to run render thread
static void RunThisThread(void* thisPtr)
{
	RenderThread* const self = reinterpret_cast<RenderThread*>(thisPtr);
	self->Run();
}

RenderThread::RenderThread(RenderEngine* pRenderEngine) :
	m_pRenderEngine(pRenderEngine),
	m_nRenderThreadId(0)
{
	m_nMainThreadId = ::GetCurrentThreadId();

	m_pThread = std::make_unique<std::thread>(RunThisThread, this);
}

// Render Loop
void RenderThread::Run()
{
	m_nRenderThreadId = ::GetCurrentThreadId();

	m_pRenderEngine->Init();

	while (true)
	{
		if (m_nCurrFrame == m_nFrameToFill)
		{
			std::unique_lock lock(frameMutex[m_nCurrFrame]);
			cv.wait(lock, [this] {return m_commandListIsReady; });
			m_commandListIsReady = false;
		}

		std::lock_guard<std::mutex> lock(frameMutex[m_nCurrFrame]);

		ProcessCommands();

		m_pRenderEngine->Update();

		OnEndFrame();
	}
}

bool RenderThread::IsRenderThread() const
{
	return m_nRenderThreadId == ::GetCurrentThreadId();
}

template<typename... Args>
void RenderThread::EnqueueCommand(ERenderCommand command, Args... args)
{
	switch (command)
	{
	case RC_CreateCubeRenderObject:
		m_commands[m_nFrameToFill].push_back(
			new EnqueuedRenderCommand(
				[this](RenderProxy* renderProxy) { m_pRenderEngine->CreateCubeRenderObject(renderProxy); },
				std::forward<Args>(args)...)
		);
		break;
	default:
		assert(0);
		break;
	}

	if (IsRenderThread())
	{
		RenderCommand* command = m_commands[m_nFrameToFill].back();
		command->DoTask();
		delete command;
		m_commands[m_nFrameToFill].pop_back();
	}
}

void RenderThread::ProcessCommands()
{
	for (auto& command : m_commands[m_nCurrFrame])
		command->DoTask();

	m_commands[m_nCurrFrame].clear();
}

void RenderThread::OnEndFrame()
{
	SwitchFrame();

	cv.notify_one();
}

void RenderThread::SwitchFrame()
{
	if (IsRenderThread())
	{
		m_nCurrFrame = GetNextFrame(m_nCurrFrame);
	}
	else
	{
		m_nFrameToFill = GetNextFrame(m_nFrameToFill);
		
		if (m_nCurrFrame == m_nFrameToFill)
		{
			std::unique_lock lock(frameMutex[m_nFrameToFill]);
			cv.wait(lock, [this]{ return !m_commandListIsReady; });
			m_commandListIsReady = true;
		}
	}
}

size_t RenderThread::GetNextFrame(size_t frameNumber) const
{
	return (frameNumber + 1) % frameBufferCount;
}