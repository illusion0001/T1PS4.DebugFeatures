#include <stdio.h>
#include <stdint.h>

void sys_proc_rw(uint64_t address, void *data, uint64_t length);
uint8_t* PatternScan(void* module, const char* signature);
