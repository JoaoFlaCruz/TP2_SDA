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
        int bytesReceived = 0;
        char buffer[1024] = { 0 };
        {
            std::lock_guard<std::mutex> lock(a_mutex);
            bytesReceived = recv(a_client_socket, buffer, sizeof(buffer) - 1, 0);
        }
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::string msg(buffer);

            MessageSocketServer* new_socket = new MessageSocketServer(a_client_socket);

            a_message_stack->insertSocketMessage(msg, new_socket);
        }
    }
}

void MessageSocketServer::sendMessage(const std::string& p_message) {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    if (p_message == "end") {
        //log_buffer->addMessage("Mensagem de encerramento recebida. Encerrando servidor...");
        //delete this;
        return;
    }

    std::string formatted_msg = formatMessage(p_message); // ajusta para 34 caracteres

    log_buffer->addMessage("Enviando mensagem: " + p_message);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    if (a_client_socket != INVALID_SOCKET) {
        std::lock_guard<std::mutex> lock(a_mutex);
        send(a_client_socket, formatted_msg.c_str(), static_cast<int>(formatted_msg.size()), 0);
    }
    else {
        log_buffer->addMessage("Socket inválido, não foi possível enviar a mensagem.");
    }
}


std::string MessageSocketServer::formatMessage(const std::string& raw) {
    std::string msg = raw;
    if (msg.size() < 34) {
        msg.append(34 - msg.size(), ' '); // preenche com espaços
    }
    else if (msg.size() > 34) {
        msg = msg.substr(0, 34); // trunca para 34 caracteres
    }
    return msg;
}
