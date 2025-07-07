#pragma once
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <process.h>
#include <mutex>
#include "LogBuffer.h"
#include <thread>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

typedef unsigned (WINAPI* CAST_FUNCTION)(LPVOID);
typedef unsigned* CAST_LPDWORD;

class MessageSocketClient
{
protected:
    SOCKET a_client_socket;
public:
    MessageSocketClient(SOCKET p_client_socket = INVALID_SOCKET);
    ~MessageSocketClient();

    void sendMessage(const std::string& p_message);
    std::string formatMessage(const std::string& raw);
};
