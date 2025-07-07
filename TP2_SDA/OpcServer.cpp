#include "OpcServer.h"

OpcServer::OpcServer(std::string p_server_name)
    : a_server_name(p_server_name)
{
    LogBuffer* log_buffer = LogBuffer::getInstance();

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring w_server_name = converter.from_bytes(a_server_name);
    const wchar_t* prog_id = w_server_name.c_str();
    CLSID CLSID_OPCServer;
    HRESULT hr;

    hr = CLSIDFromString(prog_id, &CLSID_OPCServer);
    _ASSERT(!FAILED(hr));

    LONG cmq = 1;
    MULTI_QI queue[1] =
        { {&IID_IOPCServer,
        NULL,
        0} };

    hr = CoCreateInstanceEx(CLSID_OPCServer, NULL, CLSCTX_SERVER, NULL, cmq, queue);
    _ASSERT(!hr);

    a_iopc_server = (IOPCServer*) queue[0].pItf;

    log_buffer->addMessage("Servidor OPC DA " + a_server_name + " vinculado");
}

OpcServer::~OpcServer() {
    LogBuffer* log_buffer = LogBuffer::getInstance();
    log_buffer->addMessage("Encerrando conexão com o servidor " + a_server_name);
}

bool OpcServer::addGroup(const std::string p_group_name)
{
    if (a_groups.find(p_group_name) != a_groups.end())
        return false;

    a_groups[p_group_name] = std::make_unique<OpcGroup>(p_group_name, (IOPCServer*&) a_iopc_server);
    return true;
}

OpcGroup* OpcServer::getGroup(const std::string p_group_name)
{
    auto it = a_groups.find(p_group_name);
    if (it != a_groups.end())
        return it->second.get();
    return nullptr;
}

bool OpcServer::removeGroup(const std::string p_group_name)
{
    return a_groups.erase(p_group_name) > 0;
}

bool OpcServer::addTree(const std::string p_string)
{
    // Vazio
    return true;
}

std::string OpcServer::getTree()
{
    // Vazio
    return "";
}

std::string OpcServer::readData()
{
    // Vazio
    return "";
}