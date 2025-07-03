#include "OpcItem.h"

OpcItem::OpcItem(std::string p_item_name, std::string p_item_type, std::string p_upper_name)
	: a_item_name(p_item_name),
	a_item_type(p_item_type),
	a_upper_name(p_upper_name),
	a_item_value("")
{
	// Vazio
}

OpcItem::~OpcItem() {
	// Vazio
}