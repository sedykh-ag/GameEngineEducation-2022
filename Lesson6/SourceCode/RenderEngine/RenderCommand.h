#pragma once

#include <tuple>
#include <utility>
#include <functional>

class RENDERENGINE_API RenderCommand
{
public:
	virtual void DoTask() = 0;
};

template<typename LAMBDA, typename... Args>
class RENDERENGINE_API EnqueuedRenderCommand final : public RenderCommand
{
public:

	EnqueuedRenderCommand(LAMBDA&& InLambda, Args... args) :
		lambda(std::forward<LAMBDA>(InLambda)),
		arguments(std::forward<Args>(args)...)
	{
	}

	virtual void DoTask() override
	{
		std::apply(lambda, arguments);
	}

private:
	LAMBDA lambda;
	std::tuple<Args...> arguments;
};