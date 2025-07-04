#pragma once
#define WIN32_LEAN_AND_MEAN
#include "StringMessage.h"
class DPMessage :
    public StringMessage
{
protected:
    int a_code = 0;
    int a_prod_cell_id = 0;
    int a_prod_pieces_number = 0;
    float a_act_prod_rhythm = 0.0f;
    float a_oee = 0.0f;
public:
    DPMessage(
        int p_seq_message_number, int p_prod_cell_id, int p_prod_pieces_number,
        float p_act_prod_rhythm, float p_oee);
    ~DPMessage();

    static StringMessage* buildSelf(const std::vector<std::string>& values);

    std::string getMessage() override;
    StringMessage* getResponse() override;
};

