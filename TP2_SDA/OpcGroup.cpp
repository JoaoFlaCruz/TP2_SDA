#include "OpcGroup.h"

OpcGroup::OpcGroup(std::string a_group_name, IOPCServer* p_iopc_server, IOPCItemMgt* p_iopc_item_mgt)
    : a_group_name(a_group_name),
    a_iopc_server(p_iopc_server),
    a_iopc_item_mgt(p_iopc_item_mgt)
{
    LogBuffer* log_buffer = LogBuffer::getInstance();

    DWORD dwUpdateRate = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<OPCHANDLE> dist(10000000, 99999999);
    a_client_handle_group = dist(gen);

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring w_group_name = converter.from_bytes(a_group_name);
    const wchar_t* group_name = w_group_name.c_str();
    DWORD opc_server_req_update_rate = OPC_SERVER_REQ_UPDATE_RATE;
    DWORD dw_update_rate = 0;

    HRESULT hr = a_iopc_server->AddGroup(
        group_name,
        TRUE,
        opc_server_req_update_rate,
        a_client_handle_group,
        0,
        0,
        0,
        &a_server_handle_group,
        &dw_update_rate,
        IID_IOPCItemMgt,
        (IUnknown**) &a_iopc_item_mgt);
    _ASSERT(!FAILED(hr));

    log_buffer->addMessage("Grupo " + a_group_name + " adicionado [ATIVO]");
}

OpcGroup::~OpcGroup() {
    // Recursos gerenciados automaticamente por unique_ptr
}

bool OpcGroup::setActive() {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    HRESULT hr;
    IOPCGroupStateMgt* pIOPCGroupStateMgt;
    DWORD RevisedUpdateRate;
    BOOL ActiveFlag = TRUE;

    // Get a pointer to the IOPCGroupStateMgt interface:
    hr = a_iopc_item_mgt->QueryInterface(__uuidof(pIOPCGroupStateMgt),
        (void**)&pIOPCGroupStateMgt);
    if (hr != S_OK) {
        log_buffer->addMessage("Could not obtain a pointer to IOPCGroupStateMgt. Error = " + std::to_string(hr));
        return false;
    }
    // Set the state to Active. Since the other group properties are to remain
    // unchanged we pass NULL pointers to them as suggested by the OPC DA Spec.
    hr = pIOPCGroupStateMgt->SetState(
        NULL,                // *pRequestedUpdateRate
        &RevisedUpdateRate,  // *pRevisedUpdateRate - can´t be NULL
        &ActiveFlag,		 // *pActive
        NULL,				 // *pTimeBias
        NULL,				 // *pPercentDeadband
        NULL,				 // *pLCID
        NULL);				 // *phClientGroup

    if (hr != S_OK)
        log_buffer->addMessage("Failed call to IOPCGroupMgt::SetState. Error = " + std::to_string(hr));
    else
        // Free the pointer since we will not use it anymore.
        pIOPCGroupStateMgt->Release();

    log_buffer->addMessage("Grupo " + a_group_name + " foi ativado [ATIVO]");
    return true;
}

bool OpcGroup::setInactive() {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    HRESULT hr;
    IOPCGroupStateMgt* pIOPCGroupStateMgt;
    DWORD RevisedUpdateRate;
    BOOL ActiveFlag = FALSE;

    // Get a pointer to the IOPCGroupStateMgt interface:
    hr = a_iopc_item_mgt->QueryInterface(__uuidof(pIOPCGroupStateMgt),
        (void**)&pIOPCGroupStateMgt);
    if (hr != S_OK) {
        log_buffer->addMessage("Could not obtain a pointer to IOPCGroupStateMgt. Error = " + std::to_string(hr));
        return false;
    }
    // Set the state to Active. Since the other group properties are to remain
    // unchanged we pass NULL pointers to them as suggested by the OPC DA Spec.
    hr = pIOPCGroupStateMgt->SetState(
        NULL,                // *pRequestedUpdateRate
        &RevisedUpdateRate,  // *pRevisedUpdateRate - can´t be NULL
        &ActiveFlag,		 // *pActive
        NULL,				 // *pTimeBias
        NULL,				 // *pPercentDeadband
        NULL,				 // *pLCID
        NULL);				 // *phClientGroup

    if (hr != S_OK)
        log_buffer->addMessage("Failed call to IOPCGroupMgt::SetState. Error = " + std::to_string(hr));
    else
        // Free the pointer since we will not use it anymore.
        pIOPCGroupStateMgt->Release();

    log_buffer->addMessage("Grupo " + a_group_name + " foi inativado [INATIVO]");
    return true;
}

bool OpcGroup::addItem(const std::string p_item_name)
{
    if (a_items.find(p_item_name) != a_items.end())
        return false;

    // Criação do item com tipo genérico "UNDEFINED"
    a_items[p_item_name] = std::make_unique<OpcItem>(p_item_name, "UNDEFINED", a_group_name);
    return true;
}

OpcItem* OpcGroup::getItem(const std::string p_item_name)
{
    auto it = a_items.find(p_item_name);
    if (it != a_items.end())
        return it->second.get();
    return nullptr;
}

bool OpcGroup::removeItem(const std::string p_item_name)
{
    return a_items.erase(p_item_name) > 0;
}

bool OpcGroup::addTree(std::string p_string)
{
    return true;
}

std::string OpcGroup::getTree()
{
    return "";
}
