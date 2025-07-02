#include "StringMessage.h"

StringMessage::StringMessage(int p_seq_message_number)
    : a_seq_message_number(p_seq_message_number) {}

StringMessage::~StringMessage() {}

StringMessage* StringMessage::buildSelf(const std::vector<std::string>& values) {
    return nullptr;
}

std::string StringMessage::int2string(int p_number, int left_zeros) {
    std::ostringstream oss;
    oss << std::setw(left_zeros) << std::setfill('0') << p_number;
    return oss.str();
}

std::string StringMessage::float2string(float p_number, int left_zeros, int decimal_places) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(decimal_places)
        << std::setw(left_zeros + decimal_places + 1)
        << std::setfill('0') << p_number;
    return oss.str();
}

int StringMessage::getCode() {
    return a_code;
}

int StringMessage::getSeqMessageNumber() {
    return a_seq_message_number;
}