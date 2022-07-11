#include "GameEngine.h"
#include "resource.h"

INT WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
#ifdef _DEBUG
#pragma warning(disable  : 4996)
    AllocConsole();
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);
#endif
    //LoadKeyboardLayout(L"0x409",KLF_ACTIVATE|KLF_SETFORPROCESS);
    LPCTSTR title = L"无尽射击 v1.0";
    ZY_Engine* engine = new GameEngine(hInstance, WIN_CLASS, title, IDI_LOGO, IDI_LOGO, 800, 600);//必做任务一
    ZY_Engine::pEngine = engine;
    engine->SetFrame(60);
    engine->SetShowFream(true);
    engine->StartEngine();
    delete engine;
#ifdef _DEBUG
    FreeConsole();
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);
#endif

    return TRUE;
}