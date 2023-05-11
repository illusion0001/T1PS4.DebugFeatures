#include <stdio.h>
#include <stdint.h>
#include <orbis/libkernel.h>
#include "plugin_common.h"

#define PROC_READ 0
#define PROC_WRITE 1

void WriteBytes(uint64_t address, void* data, uint64_t length);
uint8_t* PatternScan(uint64_t module_base, uint32_t module_size, const char* signature);
