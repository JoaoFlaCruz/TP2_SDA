#include "RDPMessage.h"

RDPMessage::RDPMessage(int p_seq_message_number)
    : StringMessage(p_seq_message_number) {}

RDPMessage::~RDPMessage() {}

std::string RDPMessage::getMessage() {
    return int2string(a_code, 3) + "/" + int2string(a_seq_message_number, 6);
}

StringMessage* RDPMessage::buildSelf(const std::vector<std::string>& values) {
    if (values.size() < 1) return nullptr;

    int seq = std::stoi(values[0]);

    return new RDPMessage(seq);
}