#pragma once

#include <atlbase.h>
#include <iostream>
#include <ObjIdl.h>

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

	OpcOperator();
	~OpcOperator();
public:
	static OpcOperator* getInstance();
	void readMessages();
};

