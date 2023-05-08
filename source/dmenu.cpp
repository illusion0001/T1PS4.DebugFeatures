#include "dmenu.h"
#include "memory.h"

uint64_t game_base_address = 0;

#define ALLOCATE_MEMORY_ADDR game_base_address + 0xaa5820
#define CREATE_DMENU_HEADER_ADDR game_base_address + 0x891610
#define CREATE_DMENU_ENTRY_ADDR game_base_address + 0x890af0
#define CREATE_DMENU_BOOL_ADDR game_base_address + 0x88d460
#define CREATE_DMENU_FUNC_ADDR game_base_address + 0x890550
#define APPEND_DMENU_ADDR game_base_address + 0x8919c0

bool DMenu_Test_Func(uint64_t DMenuStructure, enum DMenu_Message Message)
{
    if (Message == OnExecute)
    {
        NotifyStatic(TEX_ICON_SYSTEM,  "User clicked the button!");
        return FunctionSuccess;
    }
    return FunctionNoAction;
}

bool test_bool = false;

void CreateDMENU_Test(uint64_t root_menu)
{
    if (!game_base_address)
        return;
    FUNCTION_PTR(uint64_t, AllocateMemory, ALLOCATE_MEMORY_ADDR, uint32_t memory_size);
    FUNCTION_PTR(void, CreateDevMenuHeader, CREATE_DMENU_HEADER_ADDR, uint64_t allocated_memory, const char* menu_title, void* unk, void* unk1);
    FUNCTION_PTR(void, CreateDevMenuEntry, CREATE_DMENU_ENTRY_ADDR, uint64_t allocated_memory, const char* menu_entry_title, uint64_t root_menu_ptr, void* unk, void* unk1);
    FUNCTION_PTR(void, CreateDevMenuBool, CREATE_DMENU_BOOL_ADDR, uint64_t allocated_memory, const char* menu_bool_title, bool* bool_var);
    FUNCTION_PTR(void, CreateDevMenuFuncButton, CREATE_DMENU_FUNC_ADDR, uint64_t allocated_memory, const char* menu_func_title, void* target_func, void* arg, void* unk);
    FUNCTION_PTR(void, AppendNewMenuToRoot, APPEND_DMENU_ADDR, uint64_t root_menu_ptr, uint64_t entry_menu_ptr);
    uint64_t MyMenuPtr = AllocateMemory(DMENU_HEADER_SIZE);
    CreateDevMenuHeader(MyMenuPtr, "Test Menu", NULL, NULL);
    uint64_t MyBoolPtr = AllocateMemory(DMENU_BOOL_SIZE);
    CreateDevMenuBool(MyBoolPtr, "Test Bool 1", &test_bool);
    AppendNewMenuToRoot(MyMenuPtr, MyBoolPtr);
    uint64_t MyFuncPtr = AllocateMemory(DMENU_FUNC_SIZE);
    CreateDevMenuFuncButton(MyFuncPtr, "Test Func 1", (void*)DMenu_Test_Func, NULL, NULL);
    AppendNewMenuToRoot(MyMenuPtr, MyFuncPtr);
    uint64_t MyEntryMenuPtr = AllocateMemory(DMENU_ENTRY_SIZE);
    CreateDevMenuEntry(MyEntryMenuPtr, "Test...", MyMenuPtr, NULL, NULL);
    AppendNewMenuToRoot(root_menu, MyEntryMenuPtr);
    return;
}
