#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include <atlbase.h>
#include <iostream>
#include <ObjIdl.h>

#include "SimpleOPCClient_V3/opcda.h"
#include "SimpleOPCClient_V3/opcerror.h"
#include "SimpleOPCClient_V3/SOCAdviseSink.h"
#include "SimpleOPCClient_V3/SOCDataCallback.h"
#include "SimpleOPCClient_V3/SOCWrapperFunctions.h"

#include "OpcGroup.h"

class OpcServer {
private:
    std::unordered_map<std::wstring, std::unique_ptr<OpcGroup>> a_groups;
    std::wstring& a_server_name;

public:
    OpcServer(std::wstring& a_server_name);
    ~OpcServer();

    bool addGroup(const std::wstring& p_group_name);
    OpcGroup* getGroup(const std::wstring& p_group_name);
    bool removeGroup(const std::wstring& p_group_name);

    bool addTree(const std::wstring& p_string);
    std::wstring getTree();
    std::wstring readData();
};
