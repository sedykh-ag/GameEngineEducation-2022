#pragma once

#pragma warning(disable:4251)

#ifdef SCRIPTSYSTEM_EXPORTS
#define SCRIPTSYSTEM_API __declspec(dllexport)
#else
#define SCRIPTSYSTEM_API __declspec(dllimport)
#endif