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

#include "OpcItem.h"

class OpcGroup {
private:
    std::unordered_map<std::wstring, std::unique_ptr<OpcItem>> a_items;
    std::wstring a_group_name;
    std::wstring a_upper_name;

public:
    OpcGroup(std::wstring a_group_name, std::wstring a_upper_name);
    ~OpcGroup();

    bool addItem(const std::wstring p_item_name);
    OpcItem* getItem(const std::wstring p_item_name);
    bool removeItem(const std::wstring p_item_name);

    bool addTree(std::wstring p_string);
    std::wstring getTree();
    std::wstring readData();
};
