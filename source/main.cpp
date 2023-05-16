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
    // 15 bytes nop ptr.
    // 66 66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00
    AllocateMemory = (AllocateMemory_ptr)FindAndPrintPattern(module_base, module_size, Patterns::AllocateMemory, str(Patterns::AllocateMemory));
    CreateDevMenuHeader = (CreateDevMenuHeader_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuHeader, str(Patterns::CreateDevMenuHeader), -79);
    CreateDevMenuEntry = (CreateDevMenuEntry_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuEntry, str(Patterns::CreateDevMenuEntry), -59);
    CreateDevMenuBool = (CreateDevMenuBool_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuBool, str(Patterns::CreateDevMenuBool), -66);
    CreateDevMenuFuncButton = (CreateDevMenuFuncButton_ptr)FindAndPrintPattern(module_base, module_size, Patterns::CreateDevMenuFuncButton, str(Patterns::CreateDevMenuFuncButton), -28);
    AppendNewMenuToRoot = (AppendNewMenuToRoot_ptr)FindAndPrintPattern(module_base, module_size, Patterns::AppendNewMenuToRoot, str(Patterns::AppendNewMenuToRoot), -46);
    uint64_t CallAddr = FindAndPrintPattern(module_base, module_size, Patterns::DevMenuNullSubCallAddr, str(Patterns::DevMenuNullSubCallAddr));
    uint64_t EnableDevMenuAddr = FindAndPrintPattern(module_base, module_size, Patterns::ForceDevMenuArg, str(Patterns::ForceDevMenuArg));
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
        u8 enable_bool[] = {0x1};
        WriteBytes(EnableDevMenuAddr + 3, enable_bool, sizeof(enable_bool));
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
