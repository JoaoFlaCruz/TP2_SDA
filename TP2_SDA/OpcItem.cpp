#include "OpcItem.h"

OpcItem::OpcItem(std::wstring p_item_name, std::wstring p_item_type, std::wstring p_upper_name)
	: a_item_name(p_item_name),
	a_item_type(p_item_type),
	a_upper_name(p_upper_name),
	a_item_value(L"")
{
	// Vazio
}

OpcItem::~OpcItem() {
	// Vazio
}

std::wstring OpcItem::readData() {
	// Vazio
	return L"";
}