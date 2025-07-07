#pragma once
#define WIN32_LEAN_AND_MEAN
#include "StringMessage.h"

class EndMessage :
    public StringMessage
{
protected:
    int a_code = -1;
public:
    EndMessage();
    ~EndMessage() = default;

    static StringMessage* buildSelf(const std::vector<std::string>& values);

    std::string getMessage() override;
    StringMessage* getResponse() override;
};