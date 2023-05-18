namespace Patterns
{
    // should be valid for 01.00 - 01.06
    // 01.07 - 01.11 might be different
    const char* ForceDevMenuArg = "c6 45 97 00 c6 45 c3 00 48 c7 45 88 00 00 00 00 48 c7 45 b0 00 00 00 00 48 c7 45 a8 00 00 00 00";
    const char* AllocateMemory = "48 8d 15 ?? ?? ?? ?? be 10 00 00 00 31 c9 49 89 d0 e9 ?? ?? ?? ??";
    const char* CreateDevMenuHeader = "55 48 89 e5 41 57 41 56 53 50 41 89 cf 41 89 d6 48 89 fb e8 ?? ?? ?? ?? 48 8d 05 ?? ?? ?? ?? 48 83 c0 10 48 89 03 c7 83 80 00 00 00 00 00 00 00 c7 83 84 00 00 00 00 00 00 00 c6 83 88 00 00 00 01 44 89 bb 8c 00 00 00 44 89 b3 90 00 00 00";
    const char* CreateDevMenuEntry = "55 48 89 e5 41 57 41 56 41 54 53 4d 89 c4 49 89 cf 49 89 d6 48 89 fb e8 ?? ?? ?? ?? c7 83 84 00 00 00 00 00 00 00 c7 83 88 00 00 00 00 00 00 00 4c 89 63 50 48 8d 05 ?? ?? ?? ??";
    const char* CreateDevMenuBool = "55 48 89 e5 41 56 53 49 89 d6 48 89 fb e8 ?? ?? ?? ?? c7 83 84 00 00 00 00 00 00 00 c7 83 88 00 00 00 03 00 00 00";
    const char* CreateDevMenuFuncButton = "55 48 89 e5 41 57 41 56 41 54 53 45 89 c6 49 89 cc 49 89 d7 48 89 fb e8 ?? ?? ?? ?? c7 83 80 00 00 00 00 00 00 00 c7 83 84 00 00 00 00 00 00 00 c7 83 88 00 00 00 05 00 00 00";
    const char* AppendNewMenuToRoot = "48 8b 87 98 00 00 00 48 85 c0 74 1b 0f 1f 40 00";
    const char* DevMenuNullSubCallAddr = "e8 ?? ?? ?? ?? bf b0 00 00 00 e8 ?? ?? ?? ?? 49 89 c6 48 8d 35 ?? ?? ?? ?? 4c 89 f7 31 d2 31 c9 e8 ?? ?? ?? ?? bf a0 00 00 00 e8 ?? ?? ?? ?? 48 89 c3 48 8d 35 ?? ?? ?? ?? 48 8d 15 ?? ?? ?? ??";
    const char* ForceDevMenuArg_Neo = "c6 87 81 2e 00 00 00 eb";
    const char* AllocateMemory_Neo = "48 8d 15 ?? ?? ?? ?? be 10 00 00 00 31 c9 49 89 d0 e9 ?? ?? ?? ??";
    const char* CreateDevMenuHeader_Neo = "55 48 89 e5 41 57 41 56 53 50 41 89 cf 41 89 d6 48 89 fb e8 ?? ?? ?? ?? 48 8d 05 ?? ?? ?? ?? c5 f8 57 c0 48 83 c0 10 48 89 03 c7 83 80 00 00 00 00 00 00 00";
    const char* CreateDevMenuEntry_Neo = "55 48 89 e5 41 57 41 56 41 54 53 4d 89 c7 49 89 cc 49 89 d6 48 89 fb e8 54 bd ff ff 48 8d 05 ?? ?? ?? ?? c7 83 84 00 00 00 00 00 00 00 c7 83 88 00 00 00 00 00 00 00";
    const char* CreateDevMenuBool_Neo = "55 48 89 e5 41 56 53 49 89 d6 48 89 fb e8 ?? ?? ?? ?? 48 8d 05 ?? ?? ?? ?? c7 83 84 00 00 00 00 00 00 00 c7 83 88 00 00 00 03 00 00 00";
    const char* CreateDevMenuFuncButton_Neo = "55 48 89 e5 41 57 41 56 41 54 53 45 89 c6 49 89 cc 49 89 d7 48 89 fb e8 ?? ?? ?? ?? 48 8d 05 ?? ?? ?? ?? c7 83 80 00 00 00 00 00 00 00 c7 83 84 00 00 00 00 00 00 00 c7 83 88 00 00 00 05 00 00 00";
    const char* AppendNewMenuToRoot_Neo = "4c 8d 87 98 00 00 00 48 89 f0 31 f6 4c 89 c1 90";
    const char* DevMenuNullSubCallAddr_Neo = "e8 ?? ?? ?? ?? bf b0 00 00 00 e8 ?? ?? ?? ?? 49 89 c6 48 8d 35 ?? ?? ?? ?? 31 d2 31 c9 4c 89 f7 e8 ?? ?? ?? ?? bf a0 00 00 00 e8 ?? ?? ?? ?? 48 89 c3 48 8d 35 ?? ?? ?? ?? 48 8d 15 ?? ?? ?? ??";
    // Natives
    const char* GetSpawnerNative_Neo = "55 48 89 e5 41 56 53 48 83 ec 30 48 89 d0 48 89 f1 89 fa 4c 8d 75 c0 41 b8 01 00 00 00 89 d6 48 89 ca 4c 89 f7 48 89 c1 e8 b3 a9 ff ff";
    const char* EntitySpawner_Neo = "55 48 89 e5 41 57 41 56 41 55 41 54 53 48 81 ec f8 01 00 00 48 89 f3 49 89 fd 44 89 8d f0 fd ff ff 44 89 85 ec fd ff ff 48 85 d2 74 ?? c5 f8 10 02 89 8d f4 fd ff ff c5 f8 11 45 b0 c5 f8 10 42 10 c5 f8 11 45 c0 eb ??";
}
