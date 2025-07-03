#pragma once

#include <unordered_map>
#include <string>
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
#include "SimpleOPCClient_V3/SOCDataCallback.h"
#include "SimpleOPCClient_V3/SOCWrapperFunctions.h"

#include "Config.h"
#include "OpcConstants.h"
#include "OpcItem.h"
#include "LogBuffer.h"

class OpcGroup {
private:
    std::unordered_map<std::string, std::unique_ptr<OpcItem>> a_items;
    std::string a_group_name;

    OPCHANDLE a_client_handle_group;
    OPCHANDLE a_server_handle_group;
    IOPCServer* a_iopc_server = NULL;
    IOPCItemMgt* a_iopc_item_mgt = NULL;

public:
    OpcGroup(std::string p_group_name, IOPCServer* p_iopc_server, IOPCItemMgt* p_iopc_item_mgt);
    ~OpcGroup();

    bool addItem(const std::string p_item_name);
    OpcItem* getItem(const std::string p_item_name);
    bool removeItem(const std::string p_item_name);

    bool setActive();
    bool setInactive();
    bool addTree(std::string p_string);
    std::string getTree();
};
