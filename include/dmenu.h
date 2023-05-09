#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "plugin_common.h"

constexpr u32 DMENU_BOOL_SIZE = 160;
constexpr u32 DMENU_FUNC_SIZE = 160;
constexpr u32 DMENU_HEADER_SIZE = 176;
constexpr u32 DMENU_ENTRY_SIZE = 160;

extern uint64_t game_base_address;

#define FUNCTION_PTR(return_type, func_name, func_addr, ...) \
    typedef return_type (*func_name##_t)(__VA_ARGS__); \
    func_name##_t func_name = (func_name##_t)(func_addr);

#define TYPEDEF_FUNCTION_PTR(ret_type, func_name, ...) \
    typedef ret_type (*func_name##_ptr)(__VA_ARGS__); \
    extern func_name##_ptr func_name;

#define INIT_FUNCTION_PTR(func_name) \
    func_name##_ptr func_name = nullptr

TYPEDEF_FUNCTION_PTR(uint64_t, AllocateMemory, uint32_t memory_size);
TYPEDEF_FUNCTION_PTR(void, CreateDevMenuHeader, uint64_t allocated_memory, const char* menu_title, void* unk, void* unk1);
TYPEDEF_FUNCTION_PTR(void, CreateDevMenuEntry, uint64_t allocated_memory, const char* menu_entry_title, uint64_t root_menu_ptr, void* unk, void* unk1);
TYPEDEF_FUNCTION_PTR(void, CreateDevMenuBool, uint64_t allocated_memory, const char* menu_bool_title, bool* bool_var);
TYPEDEF_FUNCTION_PTR(void, CreateDevMenuFuncButton, uint64_t allocated_memory, const char* menu_func_title, void* target_func, void* arg, void* unk);
TYPEDEF_FUNCTION_PTR(void, AppendNewMenuToRoot, uint64_t root_menu_ptr, uint64_t entry_menu_ptr);

enum DMenu_Message
{
    None = 0,
    Unk1,
    Unk2,
    Unk3,
    OnExecute
};

enum DMenu_FuncReturnCode
{
    FunctionNoAction = 0,
    FunctionFailure = 0,
    FunctionSuccess = 1
};

extern "C" {
bool DMenu_Test_Func(uint64_t DMenuStructure, enum DMenu_Message Message);
void CreateDMENU_Test(uint64_t root_menu);
}
