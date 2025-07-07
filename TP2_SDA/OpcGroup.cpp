#include "OpcGroup.h"
#include "SimpleOPCClient_V3/SOCDataCallback.h"

OpcGroup::OpcGroup(std::string a_group_name, IOPCServer* p_iopc_server)
    : a_group_name(a_group_name),
    a_iopc_server(p_iopc_server),
    SOCDataCallback(this)
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
        pIOPCGroupStateMgt->Release();

    log_buffer->addMessage("Grupo " + a_group_name + " foi inativado [INATIVO]");
    return true;
}

bool OpcGroup::addItem(const std::string p_item_name)
{
    if (a_items.find(p_item_name) != a_items.end())
        return false;

    auto item = std::make_unique<OpcItem>(p_item_name, a_iopc_item_mgt);
    a_handle_to_item[item->getClientHandle()] = item.get();
    a_items[p_item_name] = std::move(item);
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

void OpcGroup::setDataCallBack(
    IUnknown* pGroupIUnknown,
    IOPCDataCallback* pSOCDataCallback,
    IConnectionPoint*& pIConnectionPoint,
    DWORD* pdwCookie)
{
    LogBuffer* log_buffer = LogBuffer::getInstance();

    HRESULT hr;

    IConnectionPointContainer* pIConnPtCont = NULL;

    hr = pGroupIUnknown->QueryInterface(__uuidof(pIConnPtCont), (void**)&pIConnPtCont);
    if (hr != S_OK) {
        log_buffer->addMessage("Could not obtain a pointer to IConnectionPointContainer. Error = " + std::to_string(hr));
        return;
    }

    hr = pIConnPtCont->FindConnectionPoint(IID_IOPCDataCallback, &pIConnectionPoint);
    if (hr != S_OK) {
        log_buffer->addMessage("Failed call to FindConnectionPoint. Error = " + std::to_string(hr));
        return;
    }

    hr = pIConnectionPoint->Advise(pSOCDataCallback, pdwCookie);
    if (hr != S_OK) {
        log_buffer->addMessage("Failed call to IConnectionPoint::Advise. Error = " + std::to_string(hr));
        *pdwCookie = 0;
    }

    pIConnPtCont->Release();
    return;
}

void OpcGroup::cancelDataCallback(IConnectionPoint* pIConnectionPoint, DWORD dwCookie)
{
    LogBuffer* log_buffer = LogBuffer::getInstance();

    HRESULT hr;

    hr = pIConnectionPoint->Unadvise(dwCookie);
    if (hr != S_OK) {
        log_buffer->addMessage("Failed call to IDataObject::DUnAdvise. Error = " + std::to_string(hr));
        dwCookie = 0;
    }

    pIConnectionPoint->Release();
    log_buffer->addMessage("IConnectionPoint callback desativado para o grupo " + a_group_name);
    return;
}

void OpcGroup::startCallback() {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    AddRef();

    log_buffer->addMessage("Preparando IConnectionPoint callback para o grupo " + a_group_name);
    setDataCallBack(a_iopc_item_mgt, this, a_iconnection_point, &a_dw_cookie);

    log_buffer->addMessage("IConnectionPoint callback configurado para o grupo " + a_group_name);
}

std::string OpcGroup::msgToString(const MSG& msg) {
    std::ostringstream oss;
    oss << "MSG { hwnd=" << msg.hwnd
        << ", message=0x" << std::hex << msg.message
        << ", wParam=0x" << std::hex << msg.wParam
        << ", lParam=0x" << std::hex << msg.lParam
        << ", time=" << std::dec << msg.time
        << ", pt=(" << msg.pt.x << "," << msg.pt.y << ") }";
    return oss.str();
}

OpcItem* OpcGroup::getItemByClientHandle(OPCHANDLE p_item_handle) {
    auto it = a_handle_to_item.find(p_item_handle);
    if (it != a_handle_to_item.end())
        return it->second;
    return nullptr;
}


