#pragma once
#define WIN32_LEAN_AND_MEAN
#include <atlbase.h>
#include <iostream>
#include <ObjIdl.h>
#include <mutex>

#include "SimpleOPCClient_V3/opcda.h"
#include "SimpleOPCClient_V3/opcerror.h"
#include "SimpleOPCClient_V3/SOCAdviseSink.h"
#include "SimpleOPCClient_V3/SOCDataCallback.h"
#include "SimpleOPCClient_V3/SOCWrapperFunctions.h"

#include "OpcConstants.h"
#include "OpcServer.h"
#include "LogBuffer.h"
#include "Config.h"

class OpcOperator
{
private:
	OpcServer* a_server = nullptr;
	std::mutex a_mutex;

	OpcOperator();
	~OpcOperator();
public:
	static OpcOperator* getInstance();

	void updateData(int p_op_number, int p_fab_recipe, float p_piece_type, float p_cel_id);
	std::vector<std::string> getData();
};

