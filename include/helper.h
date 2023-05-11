#include "memory.h"
#include "plugin_common.h"

int64_t FindAndPrintPattern(uint64_t module_base, uint32_t module_size, const char* signature, const char* pattern_name, int64_t offset = 0);
int get_module_info(OrbisKernelModuleInfo moduleInfo, const char* name, uint64_t *base, uint32_t *size);
