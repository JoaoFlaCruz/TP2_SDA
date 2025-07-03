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

class OpcItem {
private:
	std::wstring a_item_name;
	std::wstring a_upper_name;
	std::wstring a_item_value;
	std::wstring a_item_type;
public:
	OpcItem(std::wstring p_item_name, std::wstring p_item_type, std::wstring p_upper_name);
	~OpcItem();

	std::wstring readData();
};