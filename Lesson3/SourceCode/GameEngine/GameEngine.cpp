// GameEngine.cpp : Defines the entry point for the application.
//

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <vector>
#include <cstdlib>

#include "GameEngine.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "CubeGameObject.h"
#include "GameTimer.h"
#include "InputHandler.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Enable run-time memory check for debug builds.
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    GameTimer timer;

    RenderEngine* renderEngine = new RenderEngine(hInstance);
    RenderThread* renderThread = renderEngine->GetRT();
    InputHandler* inputHandler = new InputHandler();

    std::vector<CubeGameObject*> cubes(100);
    std::srand(std::time(nullptr));

    for (auto& cube : cubes) {
        int rand = std::rand() % 3;
        switch (rand)
        {
        case 0:
            cube = new CubeJumping;
            break;
        case 1:
            cube = new CubeControlled;
            break;
        case 2:
            cube = new CubeMoving;
            break;
        }

        renderThread->EnqueueCommand(RC_CreateCubeRenderObject, cube->GetRenderProxy());
    }

    int cnt = 0;
    const float spacing = 5.0f;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            cubes[cnt]->SetPosition(vec3(spacing * i, spacing * 0.0f, spacing * j));
            cnt++;
        }
    

    MSG msg = { 0 };

    timer.Start();
    timer.Reset();

    float newPositionX = 0.0f;

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
            timer.Tick();
            float dt = timer.DeltaTime();
            float t = timer.TotalTime();

            inputHandler->Update();

            // abomination
            for (auto& cube : cubes) {
                cube->UpdateDeltaTime(dt);
                cube->UpdateTotalTime(t, dt);

                if (inputHandler->GetInputState().test(eIC_GoLeft))
                    cube->UpdateAction(eIC_GoLeft, dt);
                if (inputHandler->GetInputState().test(eIC_GoRight))
                    cube->UpdateAction(eIC_GoRight, dt);
            }

            renderThread->OnEndFrame();
        }
    }

    return (int) msg.wParam;
}
