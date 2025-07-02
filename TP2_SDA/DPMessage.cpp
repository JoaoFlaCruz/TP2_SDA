#include "DPMessage.h"

DPMessage::DPMessage(int p_seq_message_number, int p_prod_cell_id, int p_prod_pieces_number,
    float p_act_prod_rhythm, float p_oee)
    : StringMessage(p_seq_message_number),
    a_prod_cell_id(p_prod_cell_id),
    a_prod_pieces_number(p_prod_pieces_number),
    a_act_prod_rhythm(p_act_prod_rhythm),
    a_oee(p_oee){}

DPMessage::~DPMessage() {}

std::string DPMessage::getMessage() {
    return int2string(a_code, 3) + 
        "/" + int2string(a_seq_message_number, 6) +
        "/" + int2string(a_prod_cell_id, 3) +
        "/" + int2string(a_prod_pieces_number, 5) +
        "/" + float2string(a_act_prod_rhythm, 4, 1) +
        "/" + float2string(a_oee, 1, 4);
}

StringMessage* DPMessage::buildSelf(const std::vector<std::string>& values) {
    if (values.size() < 5) return nullptr;

    int seq = std::stoi(values[0]);
    int prod_cell = std::stoi(values[1]);
    int pieces_number = std::stoi(values[2]);
    float prod_rhythm = std::stof(values[3]);
    float oee = std::stof(values[4]);

    return new DPMessage(seq, prod_cell, pieces_number, prod_rhythm, oee);
}