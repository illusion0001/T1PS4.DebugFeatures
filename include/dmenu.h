#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "plugin_common.h"

#define FUNCTION_PTR(return_type, func_name, func_addr, ...) \
    typedef return_type (*func_name##_t)(__VA_ARGS__); \
    func_name##_t func_name = (func_name##_t)(func_addr);

#define DMENU_BOOL_SIZE 160
#define DMENU_FUNC_SIZE 160
#define DMENU_HEADER_SIZE 176
#define DMENU_ENTRY_SIZE 160

extern uint64_t game_base_address;

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

bool DMenu_Test_Func(uint64_t DMenuStructure, enum DMenu_Message Message);
void CreateDMENU_Test(uint64_t root_menu);
