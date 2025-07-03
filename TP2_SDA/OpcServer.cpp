#include "OpcServer.h"

OpcServer::OpcServer(std::wstring& a_server_name)
    : a_server_name(a_server_name)
{
    // Vazio
}

OpcServer::~OpcServer() {
    // Vazio
}

bool OpcServer::addGroup(const std::wstring& p_group_name)
{
    if (a_groups.find(p_group_name) != a_groups.end())
        return false;

    a_groups[p_group_name] = std::make_unique<OpcGroup>(p_group_name, a_server_name);
    return true;
}

OpcGroup* OpcServer::getGroup(const std::wstring& p_group_name)
{
    auto it = a_groups.find(p_group_name);
    if (it != a_groups.end())
        return it->second.get();
    return nullptr;
}

bool OpcServer::removeGroup(const std::wstring& p_group_name)
{
    return a_groups.erase(p_group_name) > 0;
}

bool OpcServer::addTree(const std::wstring& p_string)
{
    // Vazio
    return true;
}

std::wstring OpcServer::getTree()
{
    // Vazio
    return L"";
}

std::wstring OpcServer::readData()
{
    // Vazio
    return L"";
}
