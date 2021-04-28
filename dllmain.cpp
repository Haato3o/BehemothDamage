#include "./libs/loader.h"

using namespace loader;

static uintptr_t damage_function = (uintptr_t)0x141CE1670;

void PatchDamageFunction()
{
    DWORD lpflOldProtect;

    HANDLE hProcess = GetCurrentProcess();
    VirtualProtectEx(
        hProcess,
        (LPVOID)damage_function,
        20,
        PAGE_EXECUTE_READWRITE,
        &lpflOldProtect
    );
    
    char nops[2] = { 0x90, 0x90 };

    memcpy_s((void*)(damage_function + 0xB), 2, nops, 2);

    VirtualProtectEx(
        hProcess,
        (LPVOID)damage_function,
        20,
        lpflOldProtect,
        &lpflOldProtect
    );

    LOG(DEBUG) << "Patched damage function\n";
    CloseHandle(hProcess);
}

__declspec(dllexport) extern bool Load()
{
    PatchDamageFunction();
    return true;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        return Load();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

