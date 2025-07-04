#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <vector>

class StringMessage
{
protected:
    int a_code = -1;
    int a_seq_message_number = -1;

public:
    StringMessage(int p_seq_message_number);
    ~StringMessage();

    virtual std::string getMessage() = 0;
    virtual StringMessage* getResponse() = 0;
    static StringMessage* buildSelf(const std::vector<std::string>& values);

    std::string int2string(int p_number, int left_zeros = 3);
    std::string float2string(float p_number, int left_zeros = 3, int decimal_places = 3);
    int getCode();
    int getSeqMessageNumber();
};
