#include <stdio.h>
#include <string>
#include <vector>

void sys_proc_rw(uint64_t address, void *data, uint64_t length);
std::uint8_t* PatternScan(void* module, const char* signature);
