#include <stdio.h>
#include <stdint.h>

#define PROC_READ 0
#define PROC_WRITE 1

void sys_proc_rw(uint64_t address, void* data, uint64_t length, uint64_t write_mode);
uint8_t* PatternScan(void* module, const char* signature);
