// Game Call Example: Calling game function example.

// Author: icemesh @ https://github.com/icemesh
// Author: illusion0001 @ https://github.com/illusion0001
// Repository: https://github.com/GoldHEN/GoldHEN_Plugins_Repository

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "dmenu.h"
#include "memory.h"
#include "plugin_common.h"
#include <orbis/libkernel.h>

attr_public const char *g_pluginName = "game_call_example";
attr_public const char *g_pluginDesc = "Calling game function example";
attr_public const char *g_pluginAuth = "icemesh, illusion";
attr_public uint32_t g_pluginVersion = 0x00000100; // 1.00

struct proc_info procInfo;

void __attribute__((naked)) DMenu_Hook()
{
    __asm__ (".intel_syntax noprefix\n"
            "mov rdi,qword ptr [rbp + -0x48]\n" // root menu ptr
            "call CreateDMENU_Test\n"
            "ret\n"
            ".att_syntax");
}

extern "C" {
int32_t attr_module_hidden module_start(size_t argc, const void *args)
{
    if (sys_sdk_proc_info(&procInfo) == 0)
    {
        // cxx printf crashes the prx :pensive:
        // more specific vsnprintf
        // print_proc_info();
        // final_printf("[GoldHEN] %s Plugin Started.\n", g_pluginName);
        // final_printf("[GoldHEN] <%s\\Ver.0x%08x> %s\n", g_pluginName, g_pluginVersion, __func__);
        // final_printf("[GoldHEN] Plugin Author(s): %s\n", g_pluginAuth);
        u8 hook_array[] = { 
            0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
        };
        u8 arr64[8];
        game_base_address = procInfo.base_address;
        uint64_t hookptr = (uint64_t)(void*)DMenu_Hook; // get the hook addr
        uint64_t LanSocketAddr = procInfo.base_address + 0x0001d480; // 1.00
        memcpy(arr64, &hookptr, sizeof(arr64));
        sys_proc_rw(LanSocketAddr, hook_array, sizeof(hook_array));
        sys_proc_rw(LanSocketAddr + 6, arr64, sizeof(arr64));
        uint64_t test_addr = (uint64_t)PatternScan((void*)game_base_address, "66 66 2e 0f 1f 84 00 00 00 00 00 49 83 c6 f8 49 8b 06 48 85 c0 74 f4 48 83 f8 ff 74 04 ff d0 eb ea 48 83 c4 08 5b 41 5e 41 5f 5d c3");
        u8 test_array[] = { 0x90, 0x12, 0x34 };
        sys_proc_rw(test_addr, test_array, sizeof(test_array));
    }
    else
    {
        // final_printf("Failed to get process info\n");
    }
    return 0;
}

int32_t attr_module_hidden module_stop(size_t argc, const void *args)
{
    // final_printf("[GoldHEN] <%s\\Ver.0x%08x> %s\n", g_pluginName, g_pluginVersion, __func__);
    // final_printf("[GoldHEN] %s Plugin Ended.\n", g_pluginName);
    return 0;
}
}
