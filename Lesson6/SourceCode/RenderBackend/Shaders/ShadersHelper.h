#pragma once

#include <bx/string.h>
#include <bx/file.h>
#include <memory>

namespace ShadersHelper
{
	static const bgfx::Memory* LoadMem(bx::FileReaderI* _reader, const char* _filePath)
	{
		if (bx::open(_reader, _filePath))
		{
			uint32_t size = (uint32_t)bx::getSize(_reader);
			const bgfx::Memory* mem = bgfx::alloc(size + 1);
			bx::read(_reader, mem->data, size, bx::ErrorAssert{});
			bx::close(_reader);
			mem->data[mem->size - 1] = '\0';
			return mem;
		}

		return nullptr;
	}

	static bgfx::ShaderHandle LoadShader(const char* _name)
	{
		char filePath[512];

		const char* shaderPath = "../../../Assets/Shaders/";

		bx::strCopy(filePath, BX_COUNTOF(filePath), shaderPath);
		bx::strCat(filePath, BX_COUNTOF(filePath), _name);
		bx::strCat(filePath, BX_COUNTOF(filePath), ".bin");

		std::unique_ptr<bx::FileReader> fReader = std::make_unique<bx::FileReader>();

		bgfx::ShaderHandle handle = bgfx::createShader(LoadMem(fReader.get(), filePath));
		bgfx::setName(handle, _name);

		return handle;
	}

	static bgfx::ProgramHandle LoadProgram(const char* _vsName, const char* _fsName)
	{
		bgfx::ShaderHandle vsh = LoadShader(_vsName);
		bgfx::ShaderHandle fsh = BGFX_INVALID_HANDLE;
		if (NULL != _fsName)
		{
			fsh = LoadShader(_fsName);
		}

		return bgfx::createProgram(vsh, fsh, true /* destroy shaders when program is destroyed */);
	}
}