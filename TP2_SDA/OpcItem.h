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

class OpcItem {
private:
	std::string a_item_name;
	std::string a_upper_name;
	std::string a_item_value;
	std::string a_item_type;

	OPCHANDLE a_handle_item;  // server handle to the item
public:
	OpcItem(std::string p_item_name, std::string p_item_type, std::string p_upper_name);
	~OpcItem();
};