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
#include "MessageSocketClient.h"

#pragma comment(lib, "ws2_32.lib")

typedef unsigned (WINAPI* CAST_FUNCTION)(LPVOID);
typedef unsigned* CAST_LPDWORD;

class MessageStack;

class MessageSocketServer
{
protected:
    SOCKET a_client_socket;
    MessageStack* a_message_stack;
    std::mutex a_mutex;
public:
    MessageSocketServer(SOCKET p_client_socket = INVALID_SOCKET);
    ~MessageSocketServer();

    void acceptMessages();
    void closeSocket();
};

