namespace Patterns
{
    // should be valid for 01.00 - 01.06
    // 01.07 - 01.11 might be different
    const char* AllocateMemory = "48 8d 15 ?? ?? ?? ?? be 10 00 00 00 31 c9 49 89 d0 e9 ?? ?? ?? ??";
    const char* CreateDevMenuHeader = "c6 83 94 00 00 00 00 48 c7 83 a8 00 00 00 00 00 00 00 48 c7 83 a0 00 00 00 00 00 00 00 48 c7 83 98 00 00 00 00 00 00 00";
    const char* CreateDevMenuEntry = "48 83 c0 10 48 89 03 4c 89 bb 90 00 00 00 4c 89 b3 98 00 00 00 4d 85 f6 c7 83 80 00 00 00 01 00 00 00";
    const char* CreateDevMenuBool = "41 8a 06 88 83 98 00 00 00 4c 89 73 50 c7 43 48 00 00 00 00 c7 83 80 00 00 00 01 00 00 00";
    const char* CreateDevMenuFuncButton = "c7 83 80 00 00 00 00 00 00 00 c7 83 84 00 00 00 00 00 00 00 c7 83 88 00 00 00 05 00 00 00 4c 89 63 50";
    const char* AppendNewMenuToRoot = "48 c7 46 38 00 00 00 00 48 89 7e 30 ff 87 84 00 00 00 c6 87 88 00 00 00 01 80 bf 94 00 00 00 00";
    const char* DevMenuNullSubCallAddr = "e8 ?? ?? ?? ?? bf b0 00 00 00 e8 ?? ?? ?? ?? 49 89 c6 48 8d 35 ?? ?? ?? ?? 4c 89 f7 31 d2 31 c9 e8 ?? ?? ?? ?? bf a0 00 00 00 e8 ?? ?? ?? ?? 48 89 c3 48 8d 35 ?? ?? ?? ?? 48 8d 15 ?? ?? ?? ??";
}
