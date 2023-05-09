#include "helper.h"

int64_t FindAndPrintPattern(void* module, const char* signature, int64_t offset)
{
    int64_t pointer_addr = (int64_t)PatternScan(module, signature);
    int64_t result_pointer = 0;
    if (pointer_addr)
    {
        if (offset)
        {
            result_pointer = offset + pointer_addr;
            final_printf("Pattern %s: 0x%016lx - 0x%lx = 0x%016lx\n", signature, pointer_addr, offset, result_pointer);
        }
        else
        {
            result_pointer = pointer_addr;
            final_printf("Pattern %s: 0x%016lx\n", signature, result_pointer);
        }
        return result_pointer;
    }
    else
    {
        final_printf("Pattern %s: not found!\n", signature);
        final_printf("Please adjust your patterns and try again\n");
        return 0;
    }
}
