#pragma once
#include "StringMessage.h"
class EDMessage :
    public StringMessage
{
protected:
    int a_code = 999;
    int a_op_number = 0;
    int a_fab_recipe = 0;
    float a_piece_type = 0.0f;
    float a_cell_id = 0.0f;
public:
    EDMessage(
        int p_seq_message_number, int p_op_number, int p_fab_recipe,
        float p_piece_type, float p_cell_id);
    ~EDMessage();

    static StringMessage* buildSelf(const std::vector<std::string>& values);

    std::string getMessage() override;
};

