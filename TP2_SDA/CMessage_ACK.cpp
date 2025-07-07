#include "CMessage_ACK.h"

CMessage_ACK::CMessage_ACK(int p_seq_message_number)
    : StringMessage(p_seq_message_number) {
}

CMessage_ACK::~CMessage_ACK() {}

std::string CMessage_ACK::getMessage() {
    return int2string(a_code, 3) + "/" + int2string(a_seq_message_number, 6);
}

StringMessage* CMessage_ACK::buildSelf(const std::vector<std::string>& values) {
    if (values.size() < 1) return nullptr;

    int seq = std::stoi(values[0]);

    return (StringMessage*) new CMessage_ACK(seq);
}

StringMessage* CMessage_ACK::getResponse() {
    std::vector<std::string> data;
    return (StringMessage*) EndMessage::buildSelf(data);
}