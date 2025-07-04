#pragma once

#include <unordered_map>
#include <string>
#include <sstream>
#include <memory>
#include <random>

#include <atlbase.h>
#include <iostream>
#include <ObjIdl.h>
#include <locale>
#include <codecvt>

#include "SimpleOPCClient_V3/opcda.h"
#include "SimpleOPCClient_V3/opcerror.h"
#include "SimpleOPCClient_V3/SOCAdviseSink.h"
#include "SimpleOPCClient_V3/SOCWrapperFunctions.h"

#include "Config.h"
#include "OpcConstants.h"
#include "OpcItem.h"
#include "LogBuffer.h"

class SOCDataCallback;

class OpcGroup {
private:
    std::unordered_map<std::string, std::unique_ptr<OpcItem>> a_items;
    std::string a_group_name;

    OPCHANDLE a_client_handle_group = NULL;
    OPCHANDLE a_server_handle_group = NULL;
    IOPCServer* a_iopc_server = NULL;
    IOPCItemMgt* a_iopc_item_mgt = NULL;

    IConnectionPoint* a_iconnection_point = NULL;
    DWORD a_dw_cookie = 0;
    SOCDataCallback* a_soc_data_callback = nullptr;

    std::unordered_map<OPCHANDLE, OpcItem*> a_handle_to_item;


    void setDataCallBack(
        IUnknown* pGroupIUnknown,
        IOPCDataCallback* pSOCDataCallback,
        IConnectionPoint*& pIConnectionPoint,
        DWORD* pdwCookie);
    void cancelDataCallback(IConnectionPoint* pIConnectionPoint, DWORD dwCookie);

public:
    OpcGroup(std::string p_group_name, IOPCServer* p_iopc_server);
    ~OpcGroup();

    bool addItem(const std::string p_item_name);
    OpcItem* getItem(const std::string p_item_name);
    bool removeItem(const std::string p_item_name);
    void startCallback();
    std::string msgToString(const MSG& msg);
    OpcItem* getItemByClientHandle(OPCHANDLE p_item_handle);

    bool setActive();
    bool setInactive();
    bool addTree(std::string p_string);
    std::string getTree();
};
