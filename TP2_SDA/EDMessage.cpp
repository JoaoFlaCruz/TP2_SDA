#include "EDMessage.h"

EDMessage::EDMessage(int p_seq_message_number, int p_op_number, int p_fab_recipe,
    float p_piece_type, float p_cell_id)
    : StringMessage(p_seq_message_number),
    a_op_number(p_op_number),
    a_fab_recipe(p_fab_recipe),
    a_piece_type(p_piece_type),
    a_cell_id(p_cell_id) {}

EDMessage::~EDMessage() {}

std::string EDMessage::getMessage() {
    return int2string(a_code, 3) +
        "/" + int2string(a_seq_message_number, 6) +
        "/" + int2string(a_op_number, 5) +
        "/" + int2string(a_fab_recipe, 3) +
        "/" + float2string(a_piece_type, 4, 1) +
        "/" + float2string(a_cell_id, 3, 1);
}

StringMessage* EDMessage::buildSelf(const std::vector<std::string>& values) {
    if (values.size() < 5) return nullptr;

    int seq = std::stoi(values[0]);
    int op_number = std::stoi(values[1]);
    int fab_recipe = std::stoi(values[2]);
    float piece_type = std::stof(values[3]);
    float cell_id = std::stof(values[4]);

    return new EDMessage(seq, op_number, fab_recipe, piece_type, cell_id);
}