#include "memory.h"
#include <GoldHEN.h>
#include <stdlib.h>
#include <string.h>
#include <orbis/libkernel.h>

#define ORBIS_KERNEL_PROT_CPU_RX (ORBIS_KERNEL_PROT_CPU_READ | ORBIS_KERNEL_PROT_CPU_EXEC)

void WriteBytes(uint64_t address, void* data, uint64_t length)
{
#if 0
    // this causes a kernel panic
    // even if 8 bytes aligned??
    sceKernelMprotect((void*)module_base, module_size, ORBIS_KERNEL_PROT_CPU_RW);
    memcpy((void*)address, data, length);
    sceKernelMprotect((void*)module_base, module_size, ORBIS_KERNEL_PROT_CPU_RX);
#endif

    struct proc_rw process_rw_data;
    process_rw_data.address = address;
    process_rw_data.data = data;
    process_rw_data.length = length;
    process_rw_data.write_flags = 1;
    sys_sdk_proc_rw(&process_rw_data);
}

#define MAX_PATTERN_LENGTH 256

static int pattern_to_byte(const char* pattern, uint8_t* bytes)
{
    int count = 0;
    const char* start = pattern;
    const char* end = pattern + strlen(pattern);

    for (const char* current = start; current < end; ++current)
    {
        if (*current == '?')
        {
            ++current;
            if (*current == '?')
            {
                ++current;
            }
            bytes[count++] = -1;
        }
        else
        {
            bytes[count++] = strtoul(current, (char**)&current, 16);
        }
    }
    return count;
}

/*
 * @brief Scan for a given byte pattern on a module
 *
 * @param module    Base of the module to search
 * @param signature IDA-style byte array pattern
 *
 * @returns Address of the first occurrence
 */
 // https://github.com/OneshotGH/CSGOSimple-master/blob/59c1f2ec655b2fcd20a45881f66bbbc9cd0e562e/CSGOSimple/helpers/utils.cpp#L182
uint8_t* PatternScan(uint64_t module_base, uint32_t module_size, const char* signature)
{
    if (!module_base && !module_size)
        return nullptr;
    uint8_t patternBytes[MAX_PATTERN_LENGTH];
    int patternLength = pattern_to_byte(signature, patternBytes);
    uint8_t* scanBytes = (uint8_t*)module_base;

    for (size_t i = 0; i < module_size; ++i)
    {
        bool found = true;
        for (int j = 0; j < patternLength; ++j)
        {
            if (scanBytes[i + j] != patternBytes[j] && patternBytes[j] != 0xff)
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return &scanBytes[i];
        }
    }
    return NULL;
}
