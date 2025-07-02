#pragma once
#include "StringMessage.h"
class CMessage_ACK :
    public StringMessage
{
protected:
    int a_code = 444;

public:
    CMessage_ACK(int p_seq_message_number);
    ~CMessage_ACK();

    static StringMessage* buildSelf(const std::vector<std::string>& values);

    std::string getMessage() override;
};

