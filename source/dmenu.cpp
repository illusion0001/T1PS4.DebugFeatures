#include "dmenu.h"
#include "memory.h"

uint64_t game_base_address = 0;

bool DMenu_Test_Func(uint64_t DMenuStructure, enum DMenu::Message Message)
{
    if (Message == DMenu::Message::OnExecute)
    {
        NotifyStatic(TEX_ICON_SYSTEM,  "User clicked the button!");
        return DMenu::FuncReturnCode::FunctionSuccess;
    }
    return DMenu::FuncReturnCode::FunctionNoAction;
}

bool test_bool = false;
INIT_FUNCTION_PTR(AllocateMemory);
INIT_FUNCTION_PTR(CreateDevMenuHeader);
INIT_FUNCTION_PTR(CreateDevMenuBool);
INIT_FUNCTION_PTR(CreateDevMenuFuncButton);
INIT_FUNCTION_PTR(CreateDevMenuEntry);
INIT_FUNCTION_PTR(AppendNewMenuToRoot);

void CreateDMENU_Test(uint64_t root_menu)
{
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
