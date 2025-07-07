#include "SocketMessage.h"
#include "MessageStack.h"

SocketMessage::SocketMessage(std::string p_message, MessageSocketClient* p_socket_server)
    : Message(p_message), a_socket_server(p_socket_server) {
    LogBuffer* log_buffer = LogBuffer::getInstance();
    std::vector<std::string> values = clipMessage(p_message);

    if (values.size() < 1) return;

    if (values[0] == "end") {
        a_string_message = EndMessage::buildSelf(values);
        return;
    }

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

bool SocketMessage::send() {
    StringMessage* string_message = a_string_message->getResponse();
    if (string_message != nullptr) {
        MessageStack* message_stack = MessageStack::getInstance();
        a_socket_server->sendMessage(string_message->getMessage());
        message_stack->insertSocketMessage(string_message->getMessage(), a_socket_server);
        return true;
    }
    return false;
}