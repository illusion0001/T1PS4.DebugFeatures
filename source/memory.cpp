#include "memory.h"
#include <GoldHEN.h>
#include <orbis/libkernel.h>

void sys_proc_rw(uint64_t address, void *data, uint64_t length)
{
    struct proc_rw process_rw_data;
    process_rw_data.address = address;
    process_rw_data.data = data;
    process_rw_data.length = length;
    process_rw_data.write_flags = 1;
#if (__FINAL__) == 0
    // debug_printf("process_rw_data: %p\n", &process_rw_data);
    // debug_printf("address: 0x%lx\n", process_rw_data.address);
    // debug_printf("hex_dump: ");
    // hex_dump(process_rw_data.data, process_rw_data.length);
    // debug_printf("length: 0x%lx\n", process_rw_data.length);
    // int32_t ret = sys_sdk_proc_rw(&process_rw_data);
    // debug_printf("sys_sdk_proc_rw: returned 0x%08x\n", ret);
#else
    sys_sdk_proc_rw(&process_rw_data);
#endif
    return;
}

static auto pattern_to_byte(const char *pattern) {
    auto bytes = std::vector<int>{};
    auto start = const_cast<char *>(pattern);
    auto end = const_cast<char *>(pattern) + strlen(pattern);

    for (auto current = start; current < end; ++current) {
        if (*current == '?') {
            ++current;
            if (*current == '?')
                ++current;
            bytes.push_back(-1);
        } else {
            bytes.push_back(strtoul(current, &current, 16));
        }
    }
    return bytes;
}

/*
 * @brief Scan for a given byte pattern on a module
 *
 * @param module    Base of the module to search
 * @param signature IDA-style byte array pattern
 *
 * @returns Address of the first occurence
 */
 // https://github.com/OneshotGH/CSGOSimple-master/blob/59c1f2ec655b2fcd20a45881f66bbbc9cd0e562e/CSGOSimple/helpers/utils.cpp#L182
std::uint8_t *PatternScan(void *module, const char *signature) {
    OrbisKernelModuleInfo tmpInfo;
    sceKernelGetModuleInfo(0, &tmpInfo);
    size_t sizeOfImage = tmpInfo.size;
    auto patternBytes = pattern_to_byte(signature);
    auto scanBytes = reinterpret_cast<std::uint8_t *>(module);

    auto s = patternBytes.size();
    auto d = patternBytes.data();

    for (auto i = 0ul; i < sizeOfImage - s; ++i) {
        bool found = true;
        for (auto j = 0ul; j < s; ++j) {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return &scanBytes[i];
        }
    }
    return nullptr;
}
