#pragma once

#include <unordered_map>
#include <string>
#include <memory>

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

#include "OpcConstants.h"
#include "OpcGroup.h"
#include "LogBuffer.h"

class OpcServer {
private:
    std::unordered_map<std::string, std::unique_ptr<OpcGroup>> a_groups;
    std::string a_server_name;

    IOPCServer* a_iopc_server = NULL;   //pointer to IOPServer interface
    IOPCItemMgt* a_iopc_item_mgt = NULL; //pointer to IOPCItemMgt interface

public:
    OpcServer(std::string p_server_name);
    ~OpcServer();

    bool addGroup(const std::string p_group_name);
    OpcGroup* getGroup(const std::string p_group_name);
    bool removeGroup(const std::string p_group_name);

    bool addTree(const std::string p_string);
    std::string getTree();
    std::string readData();
};
