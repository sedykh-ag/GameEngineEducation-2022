#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "Common.h"
#include "RenderCommand.h"

namespace
{
	extern constexpr size_t frameBufferCount = 2;
}

typedef unsigned long threadID;

class RenderEngine;

enum ERenderCommand : UINT32
{
	RC_CreateCubeRenderObject = 0,
};

class RENDERENGINE_API RenderThread
{
public:
	RenderThread() = delete;
	RenderThread(RenderEngine* pRenderEngine);

	void Run();

	template<typename... Args>
	void EnqueueCommand(ERenderCommand command, Args... args);

	bool IsRenderThread() const;
	void OnEndFrame();

private:
	void ProcessCommands();
	void SwitchFrame();
	size_t GetNextFrame(size_t frameNumber) const;

	threadID m_nRenderThreadId;
	threadID m_nMainThreadId;
	std::unique_ptr<std::thread> m_pThread;
	std::condition_variable cv;
	std::mutex frameMutex[frameBufferCount];
	bool m_commandListIsReady = false;

	RenderEngine* const m_pRenderEngine;
	
	size_t m_nCurrFrame = 0;
	size_t m_nFrameToFill = 0;

	std::vector<RenderCommand*> m_commands[frameBufferCount];
};

