// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"

#include "inih/INIReader.h"
#include <cctype>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    INIReader reader("config/actionmap.ini");

    const char leftKey = std::toupper(reader.Get("Keyboard", "GoLeft", "a").at(0));
    const char rightKey = std::toupper(reader.Get("Keyboard", "GoRight", "d").at(0));
    const char upKey = std::toupper(reader.Get("Keyboard", "GoUp", "w").at(0));
    const char downKey = std::toupper(reader.Get("Keyboard", "GoDown", "s").at(0));

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();

    GameObject* cube = new CubeGameObject();
    cube->SetPosition(0.0f, 0.0f, 0.0f);
    renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    // Main message loop:
    while (msg.message != (WM_QUIT | WM_CLOSE))
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            
            float dt = 0.0f;
            timer.Tick();
            dt = timer.DeltaTime();

            // Keyboard events
            if (GetAsyncKeyState(leftKey) & 0x8000) {
                cube->MovePosition(-5.0f * dt, 0.0f, 0.0f);
            }
            if (GetAsyncKeyState(rightKey) & 0x8000) {
                cube->MovePosition(5.0f * dt, 0.0f, 0.0f);
            }
            if (GetAsyncKeyState(upKey) & 0x8000) {
                cube->MovePosition(0.0f, 0.0f, 5.0f * dt);
            }
            if (GetAsyncKeyState(downKey) & 0x8000) {
                cube->MovePosition(0.0f, 0.0f, -5.0f * dt);
            }

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
