#pragma once
#include "StringMessage.h"
class CRMessage_ACK :
    public StringMessage
{
protected:
    int a_code = 222;

public:
    CRMessage_ACK(int p_seq_message_number);
    ~CRMessage_ACK();

    static StringMessage* buildSelf(const std::vector<std::string>& values);

    std::string getMessage() override;
};

