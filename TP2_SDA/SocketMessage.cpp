#include "SocketMessage.h"

SocketMessage::SocketMessage(std::string p_message, MessageSocketServer* p_socket_server)
    : Message(p_message), a_socket_server(p_socket_server) {
    LogBuffer* log_buffer = LogBuffer::getInstance();
    std::vector<std::string> values = clipMessage(p_message);

    if (values.size() < 1) return;

    int code = std::stoi(values[0]);
    values.erase(values.begin());

    switch (code) {
    case 0:
        a_string_message = DPMessage::buildSelf(values);
        break;
    case 999:
        a_string_message = EDMessage::buildSelf(values);
        break;
    case 333:
        a_string_message = RDPMessage::buildSelf(values);
        break;
    case 444:
        a_string_message = CMessage_ACK::buildSelf(values);
        break;
    case 222:
        a_string_message = CRMessage_ACK::buildSelf(values);
        break;
    default:
        log_buffer->addMessage(std::string("Código desconhecido: " + code));
        break;
    }
}

SocketMessage::~SocketMessage() {}