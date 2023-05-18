// Game Call Example: Calling game function example.

// Author: icemesh @ https://github.com/icemesh
// Author: illusion0001 @ https://github.com/illusion0001
// Repository: https://github.com/GoldHEN/GoldHEN_Plugins_Repository

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "dmenu.h"
#include "helper.h"
#include "memory.h"
#include "plugin_common.h"
#include "patterns.h"
#include <orbis/libkernel.h>

#define str(str) #str

attr_public const char *g_pluginName = "game_call_example";
attr_public const char *g_pluginDesc = "Calling game function example";
attr_public const char *g_pluginAuth = "icemesh, illusion";
attr_public uint32_t g_pluginVersion = 0x00000100; // 1.00

struct proc_info procInfo;

char app_version[8] = { 0 };

#define USE_THREAD 0

void __attribute__((naked)) DMenu_Hook()
{
    __asm__(".intel_syntax noprefix\n"
            "mov rdi,qword ptr [rbp + -0x48]\n" // root menu ptr
            "call CreateDMENU_Test\n"
            "ret\n"
            ".att_syntax");
}

#if USE_THREAD == 0
void DoStuff()
#else
void *DoStuff(void *args)
#endif
{
    bool neo_version = false;
    strncpy(app_version, procInfo.version, sizeof(app_version));
    float ver_app = 0.f;
    ver_app = strtod(app_version, NULL);
    if (ver_app >= 1.07)
    {
        neo_version = true;
    }
    OrbisKernelModuleInfo CurrentModuleInfo;
    CurrentModuleInfo.size = sizeof(OrbisKernelModuleInfo);
    uint64_t module_base = 0;
    uint32_t module_size = 0;
    if(!get_module_info(CurrentModuleInfo, "0", &module_base, &module_size))
    {
        final_printf("Could not find module info for current process\n");
#if USE_THREAD == 0
        return;
#else
        scePthreadExit(NULL);
        return NULL;
#endif
    }
    final_printf("module_base: 0x%lx\n", module_base);
    final_printf("module_size: 0x%x\n", module_size);
    uint64_t CallAddr = 0;
    uint64_t EnableDevMenuAddr = 0;
    // 15 bytes nop ptr.
    // 66 66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00
    if (!neo_version)
    {
        AllocateMemory = (AllocateMemory_ptr)FindAndPrintPattern(module_base, module_size, Patterns::AllocateMemory, str(Patterns::AllocateMemory));
        CreateDevMenuHeader = (CreateDevMenuHeader_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuHeader, str(Patterns::CreateDevMenuHeader));
        CreateDevMenuEntry = (CreateDevMenuEntry_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuEntry, str(Patterns::CreateDevMenuEntry));
        CreateDevMenuBool = (CreateDevMenuBool_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuBool, str(Patterns::CreateDevMenuBool));
        CreateDevMenuFuncButton = (CreateDevMenuFuncButton_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuFuncButton, str(Patterns::CreateDevMenuFuncButton));
        AppendNewMenuToRoot = (AppendNewMenuToRoot_ptr)FindAndPrintPattern(module_base, module_size, Patterns::AppendNewMenuToRoot, str(Patterns::AppendNewMenuToRoot));
        CallAddr = FindAndPrintPattern(module_base, module_size, Patterns::DevMenuNullSubCallAddr, str(Patterns::DevMenuNullSubCallAddr));
        EnableDevMenuAddr = FindAndPrintPattern(module_base, module_size, Patterns::ForceDevMenuArg, str(Patterns::ForceDevMenuArg));
    }
    else
    {
        AllocateMemory = (AllocateMemory_ptr)FindAndPrintPattern(module_base, module_size, Patterns::AllocateMemory_Neo, str(Patterns::AllocateMemory_Neo));
        CreateDevMenuHeader = (CreateDevMenuHeader_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuHeader_Neo, str(Patterns::CreateDevMenuHeader_Neo));
        CreateDevMenuEntry = (CreateDevMenuEntry_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuEntry_Neo, str(Patterns::CreateDevMenuEntryCreateDevMenuEntry_Neo));
        CreateDevMenuBool = (CreateDevMenuBool_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuBool_Neo, str(Patterns::CreateDevMenuBool_Neo));
        CreateDevMenuFuncButton = (CreateDevMenuFuncButton_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuFuncButton_Neo, str(Patterns::CreateDevMenuFuncButton_Neo));
        AppendNewMenuToRoot = (AppendNewMenuToRoot_ptr)FindAndPrintPattern(module_base, module_size, Patterns::AppendNewMenuToRoot_Neo, str(Patterns::AppendNewMenuToRoot_Neo));
        CallAddr = FindAndPrintPattern(module_base, module_size, Patterns::DevMenuNullSubCallAddr_Neo, str(Patterns::DevMenuNullSubCallAddr_Neo));
        EnableDevMenuAddr = FindAndPrintPattern(module_base, module_size, Patterns::ForceDevMenuArg_Neo, str(Patterns::ForceDevMenuArg_Neo));
        GetSpawnerNativeFunc = (GetSpawnerNativeFunc_ptr)FindAndPrintPattern(module_base, module_size, Patterns::GetSpawnerNative_Neo, str(Patterns::GetSpawnerNative_Neo));
        EntitySpawnerFunc = (EntitySpawnerFunc_ptr)FindAndPrintPattern(module_base, module_size, Patterns::EntitySpawner_Neo, str(Patterns::EntitySpawner_Neo));
    }
    if (
        AllocateMemory &&
        CreateDevMenuHeader &&
        CreateDevMenuEntry &&
        CreateDevMenuBool &&
        CreateDevMenuFuncButton &&
        AppendNewMenuToRoot &&
        CallAddr &&
        EnableDevMenuAddr)
    {
        u8 hook_array[] = {
            0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,            // jmp qword ptr [$+6]
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
        };
        int32_t offset_addr = *(int32_t*)(CallAddr + 1);
        u8 arr64[8];
        uint64_t hookptr = (uint64_t)(void *)DMenu_Hook; // get the hook addr
        uint64_t LanSocketAddr = CallAddr + offset_addr + 5;
        memcpy(arr64, &hookptr, sizeof(arr64));
        WriteBytes(LanSocketAddr, hook_array, sizeof(hook_array));
        WriteBytes(LanSocketAddr + 6, arr64, sizeof(arr64));
        u8 enable_bool[] = { 0x1 };
        if (!neo_version)
        {
            WriteBytes(EnableDevMenuAddr + 3, enable_bool, sizeof(enable_bool));
        }
        else
        {
            WriteBytes(EnableDevMenuAddr + 6, enable_bool, sizeof(enable_bool));
        }
    }
#if USE_THREAD == 0
#else
    scePthreadExit(NULL);
    return NULL;
#endif
}

extern "C"
{
int32_t attr_module_hidden module_start(size_t argc, const void *args)
{
    if (sys_sdk_proc_info(&procInfo) == 0)
    {
        game_base_address = procInfo.base_address;
        boot_ver();
        print_proc_info();
        final_printf("[GoldHEN] %s Plugin Started.\n", g_pluginName);
        final_printf("[GoldHEN] <%s\\Ver.0x%08x> %s\n", g_pluginName, g_pluginVersion, __func__);
        final_printf("[GoldHEN] Plugin Author(s): %s\n", g_pluginAuth);
#if USE_THREAD == 0
        DoStuff();
#else
        // NotifyStatic(TEX_ICON_SYSTEM, "Threading mode");
        OrbisPthread thread;
        scePthreadCreate(&thread, NULL, DoStuff, NULL, "DoStuff");
#endif
    }
    else
    {
        final_printf("Failed to get process info\n");
    }
    return 0;
}

int32_t attr_module_hidden module_stop(size_t argc, const void *args)
{
    final_printf("[GoldHEN] <%s\\Ver.0x%08x> %s\n", g_pluginName, g_pluginVersion, __func__);
    final_printf("[GoldHEN] %s Plugin Ended.\n", g_pluginName);
    return 0;
}
}
