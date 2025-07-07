#include "MessageSocketClient.h"

MessageSocketClient::MessageSocketClient(SOCKET p_socket) : a_client_socket(p_socket) {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    if (p_socket == INVALID_SOCKET) {
        log_buffer->addMessage(std::string("Socket inválido passado ao servidor!"));
        return;
    }
}

MessageSocketClient::~MessageSocketClient() {}

void MessageSocketClient::sendMessage(const std::string& p_message) {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    if (p_message == "end") {
        //log_buffer->addMessage("Mensagem de encerramento recebida. Encerrando servidor...");
        delete this;
        return;
    }

    std::string formatted_msg = formatMessage(p_message); // ajusta para 34 caracteres

    log_buffer->addMessage("Enviando mensagem: " + p_message);

    if (a_client_socket != INVALID_SOCKET) {
        send(a_client_socket, formatted_msg.c_str(), static_cast<int>(formatted_msg.size()), 0);
    }
    else {
        log_buffer->addMessage("Socket inválido, não foi possível enviar a mensagem.");
    }
}


std::string MessageSocketClient::formatMessage(const std::string& raw) {
    std::string msg = raw;
    if (msg.size() < 34) {
        msg.append(34 - msg.size(), ' '); // preenche com espaços
    }
    else if (msg.size() > 34) {
        msg = msg.substr(0, 34); // trunca para 34 caracteres
    }
    return msg;
}
