#include "Message.h"

Message::Message(std::string p_message) : a_string_message(nullptr) {}

Message::~Message() {}

std::vector<std::string> Message::clipMessage(const std::string& p_message) {
    std::vector<std::string> result;
    std::stringstream ss(p_message);
    std::string token;

    while (std::getline(ss, token, '/')) {
        result.push_back(token);
    }

    return result;
}

bool Message::send() {
    return false;
}

std::string Message::toString() {
    return a_string_message->getMessage();
}