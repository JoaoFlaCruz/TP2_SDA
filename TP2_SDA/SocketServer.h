#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <process.h>
#include <thread>
#include <string>
#include <deque>

#include "MessageSocketServer.h"
#include "LogBuffer.h";

#pragma comment(lib, "ws2_32.lib")

typedef unsigned (WINAPI* CAST_FUNCTION)(LPVOID);
typedef unsigned* CAST_LPDWORD;

class SocketServer {
protected:
    WSADATA a_wsa_data;
    SOCKET a_listen_socket = INVALID_SOCKET;
    sockaddr_in a_server_addr{};

public:
    SocketServer(SOCKET p_socket = INVALID_SOCKET);
    ~SocketServer();

    void initializeSocket();
    void bindSocket(int p_port);
    void listenSocket();
    void closeSocket();
};
