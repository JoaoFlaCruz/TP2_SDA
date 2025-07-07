#pragma once
#define WIN32_LEAN_AND_MEAN
#include "StringMessage.h"
#include "DPMessage.h"
#include "OpcOperator.h"

class RDPMessage :
    public StringMessage
{
protected:
    int a_code = 333;

public:
    RDPMessage(int p_seq_message_number);
    ~RDPMessage();

    static StringMessage* buildSelf(const std::vector<std::string>& values);

    std::string getMessage() override;
    StringMessage* getResponse() override;
};

