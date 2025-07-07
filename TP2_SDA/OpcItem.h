#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <random>
#include <iomanip>
#include <sstream>

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
#include "LogBuffer.h"
#include "LogOpc.h"

#define VT VT_R4

class OpcItem {
public:
	std::string a_item_name;
	std::string a_item_value = "";
	std::string a_item_quality = "";
	std::string a_item_timestamp = "";

	OPCHANDLE a_client_handle_item = NULL;
	OPCHANDLE a_server_handle_item = NULL;
	IOPCServer* a_iopc_server = NULL;
	IOPCItemMgt* a_iopc_item_mgt = NULL;
public:
	OpcItem(std::string p_item_name, IOPCItemMgt* p_iopc_item_mgt);
	~OpcItem();
	void handleDataChange(const char* p_value, WORD p_quality, SYSTEMTIME p_timestamp);
	OPCHANDLE getClientHandle();	
	bool writeValue(const std::string& p_value);
	std::string getValue();
};