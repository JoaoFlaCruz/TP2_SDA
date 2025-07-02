#include "MessageSocketServer.h"
#include "MessageStack.h"

MessageSocketServer::MessageSocketServer(SOCKET p_socket) : a_message_stack(nullptr), a_client_socket(p_socket) {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    if (p_socket == INVALID_SOCKET) {
        log_buffer->addMessage(std::string("Socket inválido passado ao servidor!"));
        return;
    }

    a_message_stack = MessageStack::getInstance();
}

MessageSocketServer::~MessageSocketServer() {
    closeSocket();
    _endthreadex(0);
}

void MessageSocketServer::closeSocket() {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    if (a_client_socket != INVALID_SOCKET) {
        closesocket(a_client_socket);
        log_buffer->addMessage(std::string("Socket fechado."));
    }
}

void MessageSocketServer::acceptMessages() {
    LogBuffer* log_buffer = LogBuffer::getInstance();
    log_buffer->addMessage(std::string("Aguardando mensagens do cliente..."));

    while (true) {
        char buffer[1024] = { 0 };
        int bytesReceived = recv(a_client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::string msg(buffer);

            a_message_stack->insertSocketMessage(msg, this);
        }
    }
}
