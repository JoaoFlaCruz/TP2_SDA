#include "SocketServer.h"

SocketServer::SocketServer(SOCKET p_socket) {}

SocketServer::~SocketServer() {
    closeSocket();
    WSACleanup();
}

void SocketServer::initializeSocket() {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    log_buffer->addMessage(std::string("Criando socket."));
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &a_wsa_data);
    if (wsaResult != 0) {
        log_buffer->addMessage(std::string("WSAStartup falhou: " + std::to_string(wsaResult)));
        exit(EXIT_FAILURE);
    }

    a_listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (a_listen_socket == INVALID_SOCKET) {
        log_buffer->addMessage(std::string("Erro ao criar socket: " + WSAGetLastError()));
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    log_buffer->addMessage(std::string("Socket criado com sucesso."));
}

void SocketServer::bindSocket(int port) {
    LogBuffer* log_buffer = LogBuffer::getInstance();
    a_server_addr.sin_family = AF_INET;
    a_server_addr.sin_port = htons(port);
    a_server_addr.sin_addr.s_addr = INADDR_ANY;

    int result = bind(a_listen_socket, (SOCKADDR*)&a_server_addr, sizeof(a_server_addr));
    if (result == SOCKET_ERROR) {
        log_buffer->addMessage(std::string("Erro no bind: " + WSAGetLastError()));
        closesocket(a_listen_socket);
        WSACleanup();
    }

    log_buffer->addMessage(std::string("Socket vinculado à porta " + std::to_string(port)));
}

void SocketServer::listenSocket() {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    int result = listen(a_listen_socket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        log_buffer->addMessage("Erro ao escutar a porta.");
        closesocket(a_listen_socket);
        WSACleanup();
        return;
    }

    log_buffer->addMessage("Servidor aguardando conexão...");

    while (true) {
        sockaddr_in client_addr;
        int client_len = sizeof(client_addr);
        SOCKET client_socket = accept(a_listen_socket, (SOCKADDR*)&client_addr, &client_len);
        if (client_socket == INVALID_SOCKET) {
            log_buffer->addMessage("Erro ao aceitar conexão.");
            WSACleanup();
        }

        log_buffer->addMessage("Conexão aceita com sucesso.");

        std::thread([client_socket]() {
            MessageSocketServer new_socket(client_socket);
            new_socket.acceptMessages();

            closesocket(client_socket);
            }).detach();

        log_buffer->addMessage("Conexão repassada para thread com sucesso.");
    }
}



void SocketServer::closeSocket() {
    LogBuffer* log_buffer = LogBuffer::getInstance();
    if (a_listen_socket != INVALID_SOCKET) {
        closesocket(a_listen_socket);
        log_buffer->addMessage("Socket fechado.");
    }
}

