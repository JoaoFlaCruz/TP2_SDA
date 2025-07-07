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

    return (StringMessage*) new RDPMessage(seq);
}

StringMessage* RDPMessage::getResponse() {
    std::vector<std::string> data;

    auto prom = std::make_shared<std::promise<std::vector<std::string>>>();
    std::future<std::vector<std::string>> fut = prom->get_future();

    OpcOperator::getInstance()->enqueue(OpcOperator::Command{
        [prom]() {
            std::vector<std::string> result = OpcOperator::getInstance()->getData();
            prom->set_value(result);
        }
        });

    data = fut.get();
    data.insert(data.begin(), std::to_string(a_seq_message_number + 1));

    return DPMessage::buildSelf(data);
}
