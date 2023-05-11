#include "helper.h"

// https://github.com/bucanero/apollo-ps4/blob/a530cae3c81639eedebac606c67322acd6fa8965/source/orbis_jbc.c#L62
int get_module_info(OrbisKernelModuleInfo moduleInfo, const char* name, uint64_t *base, uint32_t *size)
{
    OrbisKernelModule handles[256];
    size_t numModules;
    int ret = 0;
    ret = sceKernelGetModuleList(handles, sizeof(handles), &numModules);
    if (ret)
    {
        final_printf("sceKernelGetModuleList (0x%08x)\n", ret);
        return ret;
    }
    final_printf("numModules: %li\n", numModules);
    for (size_t i = 0; i < numModules; ++i)
    {
        ret = sceKernelGetModuleInfo(handles[i], &moduleInfo);
        final_printf("ret 0x%x\n", ret);
        final_printf("module %li\n", i);
        final_printf("name: %s\n", moduleInfo.name);
        final_printf("start: 0x%lx\n", (uint64_t)moduleInfo.segmentInfo[0].address);
        final_printf("size: %u (0x%x)\n", moduleInfo.segmentInfo[0].size, moduleInfo.segmentInfo[0].size);
        if (ret)
        {
            final_printf("sceKernelGetModuleInfo (%X)\n", ret);
            return ret;
        }

        if (strcmp(moduleInfo.name, name) == 0 || name[0] == '0')
        {
            if (base)
                *base = (uint64_t)moduleInfo.segmentInfo[0].address;

            if (size)
                *size = moduleInfo.segmentInfo[0].size;
            return 1;
        }
    }
    return 0;
}

int64_t FindAndPrintPattern(uint64_t module_base, uint32_t module_size, const char* signature, const char* pattern_name, int64_t offset)
{
    if (!module_base || !module_size)
    {
        final_printf("Module starting address is %li!\n", module_base);
        final_printf("Module size is %u!\n", module_size);
        return 0;
    }
    int64_t pointer_addr = (int64_t)PatternScan(module_base, module_size, signature);
    int64_t result_pointer = 0;
    if (pointer_addr)
    {
        if (offset)
        {
            result_pointer = offset + pointer_addr;
            final_printf("%s: 0x%lx - 0x%lx = 0x%lx\n", pattern_name, pointer_addr, offset, result_pointer);
        }
        else
        {
            result_pointer = pointer_addr;
            final_printf("%s: 0x%lx\n", pattern_name, result_pointer);
        }
        return result_pointer;
    }
    else
    {
        final_printf("%s: not found!\n", pattern_name);
        final_printf("Pattern: %s\n", signature);
        final_printf("Please adjust your patterns and try again\n");
        return 0;
    }
}
