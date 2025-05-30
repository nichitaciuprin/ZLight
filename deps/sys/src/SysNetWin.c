#include "SysNet.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <winsock.h>

int _SysNetDigitsToInt(const char* str, int length)
{
    // example
    // [] -> 0
    // ['0'] -> 0
    // ['1','2','3'] -> 123
    // ['0','1','2','3'] -> 123

    int result = 0;
    int f = 1;

    for (int i = length - 1; i >= 0; i--)
    {
        switch (str[i])
        {
            case '0': result += 0 * f; f*=10; break;
            case '1': result += 1 * f; f*=10; break;
            case '2': result += 2 * f; f*=10; break;
            case '3': result += 3 * f; f*=10; break;
            case '4': result += 4 * f; f*=10; break;
            case '5': result += 5 * f; f*=10; break;
            case '6': result += 6 * f; f*=10; break;
            case '7': result += 7 * f; f*=10; break;
            case '8': result += 8 * f; f*=10; break;
            case '9': result += 9 * f; f*=10; break;
        }
    }

    return result;
}

static void InitNetHelper()
{
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != NO_ERROR)
        printf("WSAStartup failed with error %d\n", result);
}

// TODO remove?
// static SOCKADDR CreateSocketAddress(const char* ip, short port)
// {
//     struct sockaddr_in addr;
//     addr.sin_family = AF_INET;
//     addr.sin_port = htons(port);
//     addr.sin_addr.s_addr = inet_addr(ip);
//     return *((SOCKADDR*)&addr);
// }

static SOCKET SysNetCreateSocketNoBind()
{
    SOCKET sock = INVALID_SOCKET;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // makes socket non-blocking
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    if (sock == INVALID_SOCKET)
        printf("socket failed with error %d\n", WSAGetLastError());

    return sock;
}
static SOCKET SysNetCreateSocket(int port)
{
    SOCKET sock = INVALID_SOCKET;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // makes socket non-blocking
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    if (sock == INVALID_SOCKET)
        printf("socket failed with error %d\n", WSAGetLastError());

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (SOCKADDR*)&addr, sizeof(addr)))
    {
        printf("bind failed with error %d\n", WSAGetLastError());
        return 1;
    }

    return sock;
}
static void SysNetSendMessage(SOCKET sock, SOCKADDR* addr, char* buffer, int messageSize)
{
    int addrSize = (sizeof(*addr));
    sendto(sock, buffer, messageSize, 0, addr, addrSize);
}
static void SysNetRecvMessage(SOCKET sock, SOCKADDR* addr, char* buffer, int* messageSize)
{
    int addrSize = (sizeof(*addr));
    int byteCount = recvfrom(sock, buffer, 1024, 0, addr, &addrSize);

    // if (byteCount > 0)
    // {
    //     char* ip = inet_ntoa(((sockaddr_in*)addr)->sin_addr);
    //     // cout << ip << endl;
    // }

    *messageSize = byteCount;
}

static SOCKET SysNetSocket;
static bool SysNetInitCalled = false;
static void SysNetInit()
{
    if (SysNetInitCalled) return;
        SysNetInitCalled = true;

    InitNetHelper();
}

uint64_t SysNetCreateAddr(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint16_t port)
{
    uint64_t ip = 0;

    ip += b1; ip = ip <<  8;
    ip += b2; ip = ip <<  8;
    ip += b3; ip = ip <<  8;
    ip += b4; ip = ip << 16;
    ip += port;

    return ip;
}
bool SysNetParseAddr(const char* str, int length, uint64_t* addr)
{
    char buff[16];
    int num[5];
    int buffc = 0;
    int numc = 0;

    for (int i = 0; i < length; i++)
    {
        char char_ = str[i];

        switch (char_)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                if (buffc == 16) return false;
                buff[buffc] = char_;
                buffc++;
                break;
            }
            case '.':
            case ':':
            {
                if (numc == 5) return false;
                num[numc] = _SysNetDigitsToInt(buff, buffc);
                buffc = 0;
                numc++;
                break;
            }
            default: return false;
        }
    }

    if (numc == 5) return false;
    num[numc] = _SysNetDigitsToInt(buff, buffc);

    if (num[0] > 255)   return false;
    if (num[1] > 255)   return false;
    if (num[2] > 255)   return false;
    if (num[3] > 255)   return false;
    if (num[4] > 65535) return false;

    *addr = SysNetCreateAddr(num[0], num[1], num[2], num[3], num[4]);

    return true;
}
void SysNetPrintAddr(uint64_t addr)
{
    { uint8_t byte = addr >> 8 * (5 - 0); int byte2 = byte; printf("%i", byte2); } printf(".");
    { uint8_t byte = addr >> 8 * (5 - 1); int byte2 = byte; printf("%i", byte2); } printf(".");
    { uint8_t byte = addr >> 8 * (5 - 2); int byte2 = byte; printf("%i", byte2); } printf(".");
    { uint8_t byte = addr >> 8 * (5 - 3); int byte2 = byte; printf("%i", byte2); } printf(":");
    { uint16_t port = addr; printf("%i", port); }
}
void SysNetPrintAddrAsHex(uint64_t addr)
{
    for (size_t i = 0; i < 6; i++)
    {
        uint8_t byte = addr >> 8 * (5 - i);
        printf("%02x", byte);
    }
}
void SysNetUseAnyPort()
{
    SysNetInit();
    SysNetSocket = SysNetCreateSocketNoBind();
}
void SysNetUsePort(int port)
{
    SysNetInit();
    SysNetSocket = SysNetCreateSocket(port);
}
void SysNetSend(uint64_t* addr, char* buffer, int* messageSize)
{
    assert(addr != NULL);
    assert(buffer != NULL);
    assert(messageSize != NULL);
    assert(*addr != 0);
    assert(*messageSize >= 0);

    struct sockaddr_in sockAddrIn;

    uint64_t id = *addr;

    // NetHelper_PrintId(id);

    uint16_t port  = id;  id = id >> 16;
    uint8_t b4     = id;  id = id >>  8;
    uint8_t b3     = id;  id = id >>  8;
    uint8_t b2     = id;  id = id >>  8;
    uint8_t b1     = id;

    sockAddrIn.sin_family = AF_INET;
    sockAddrIn.sin_addr.S_un.S_un_b.s_b1 = b1;
    sockAddrIn.sin_addr.S_un.S_un_b.s_b2 = b2;
    sockAddrIn.sin_addr.S_un.S_un_b.s_b3 = b3;
    sockAddrIn.sin_addr.S_un.S_un_b.s_b4 = b4;
    sockAddrIn.sin_port = htons(port);

    // cout << "===SEND===" << endl;
    // cout << ((int)sockAddrIn.sin_addr.S_un.S_un_b.s_b1) << endl;
    // cout << ((int)sockAddrIn.sin_addr.S_un.S_un_b.s_b2) << endl;
    // cout << ((int)sockAddrIn.sin_addr.S_un.S_un_b.s_b3) << endl;
    // cout << ((int)sockAddrIn.sin_addr.S_un.S_un_b.s_b4) << endl;

    // char* ip = inet_ntoa(sockAddrIn.sin_addr);
    // cout << ip << endl;

    SOCKADDR* sockAddr = (SOCKADDR*)&sockAddrIn;

    SysNetSendMessage(SysNetSocket, sockAddr, buffer, *messageSize);
}
void SysNetRecv(uint64_t* addr, char* buffer, int* messageSize)
{
    SOCKADDR sockAddr;

    SysNetRecvMessage(SysNetSocket, &sockAddr, buffer, messageSize);

    if (*messageSize < 0) return;

    struct sockaddr_in* sockAddrIn = (struct sockaddr_in*)&sockAddr;

    // char* ip = inet_ntoa(sockAddrIn->sin_addr);
    // cout << ip << endl;

    uint64_t id = 0;

    // cout << "===RECV===" << endl;
    // cout << ((int)sockAddrIn->sin_addr.S_un.S_un_b.s_b1) << endl;
    // cout << ((int)sockAddrIn->sin_addr.S_un.S_un_b.s_b2) << endl;
    // cout << ((int)sockAddrIn->sin_addr.S_un.S_un_b.s_b3) << endl;
    // cout << ((int)sockAddrIn->sin_addr.S_un.S_un_b.s_b4) << endl;

    id += sockAddrIn->sin_addr.S_un.S_un_b.s_b1; id = id <<  8;
    id += sockAddrIn->sin_addr.S_un.S_un_b.s_b2; id = id <<  8;
    id += sockAddrIn->sin_addr.S_un.S_un_b.s_b3; id = id <<  8;
    id += sockAddrIn->sin_addr.S_un.S_un_b.s_b4; id = id << 16;
    id += ntohs(sockAddrIn->sin_port);

    *addr = id;
}
bool SysNetIsLocalHost(uint64_t addr)
{
    uint8_t byte0 = addr >> 8 * (5 - 0); if (byte0 != 127) { return false; };
    uint8_t byte1 = addr >> 8 * (5 - 1); if (byte1 !=   0) { return false; };
    uint8_t byte2 = addr >> 8 * (5 - 2); if (byte2 !=   0) { return false; };
    uint8_t byte3 = addr >> 8 * (5 - 3); if (byte3 !=   1) { return false; };
                                                             return true;
}
