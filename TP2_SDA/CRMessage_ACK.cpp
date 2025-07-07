#include "CRMessage_ACK.h"

CRMessage_ACK::CRMessage_ACK(int p_seq_message_number)
    : StringMessage(p_seq_message_number) {
}

CRMessage_ACK::~CRMessage_ACK() {}

std::string CRMessage_ACK::getMessage() {
    return int2string(a_code, 3) + "/" + int2string(a_seq_message_number, 6);
}

StringMessage* CRMessage_ACK::buildSelf(const std::vector<std::string>& values) {
    if (values.size() < 1) return nullptr;

    int seq = std::stoi(values[0]);

    return (StringMessage*) new CRMessage_ACK(seq);
}

StringMessage* CRMessage_ACK::getResponse() {
    std::vector<std::string> data;
    return (StringMessage*) EndMessage::buildSelf(data);
}