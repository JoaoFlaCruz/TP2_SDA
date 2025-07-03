#include "OpcGroup.h"

OpcGroup::OpcGroup(std::wstring a_group_name, std::wstring a_upper_name)
    : a_group_name(a_group_name),
    a_upper_name(a_upper_name)
{
}

OpcGroup::~OpcGroup() {
    // Recursos gerenciados automaticamente por unique_ptr
}

bool OpcGroup::addItem(const std::wstring p_item_name)
{
    if (a_items.find(p_item_name) != a_items.end())
        return false;

    // Criação do item com tipo genérico "UNDEFINED"
    a_items[p_item_name] = std::make_unique<OpcItem>(p_item_name, L"UNDEFINED", a_group_name);
    return true;
}

OpcItem* OpcGroup::getItem(const std::wstring p_item_name)
{
    auto it = a_items.find(p_item_name);
    if (it != a_items.end())
        return it->second.get();
    return nullptr;
}

bool OpcGroup::removeItem(const std::wstring p_item_name)
{
    return a_items.erase(p_item_name) > 0;
}

bool OpcGroup::addTree(std::wstring p_string)
{
    return true;
}

std::wstring OpcGroup::getTree()
{
    return L"";
}

std::wstring OpcGroup::readData()
{
    return L"";
}
