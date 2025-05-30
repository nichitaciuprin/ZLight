#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t SysNetCreateAddr(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint16_t port);
bool SysNetParseAddr(const char* str, int length, uint64_t* addr);
void SysNetPrintAddr(uint64_t addr);
void SysNetPrintAddrAsHex(uint64_t addr);
void SysNetUseAnyPort();
void SysNetUsePort(int port);
void SysNetSend(uint64_t* addr, char* buffer, int* messageSize);
void SysNetRecv(uint64_t* addr, char* buffer, int* messageSize);
bool SysNetIsLocalHost(uint64_t addr);

#ifdef __cplusplus
}
#endif
