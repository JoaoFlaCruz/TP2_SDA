#pragma once

#include "MessageStack.h"
#include "LogBuffer.h";
#include <mutex>

class CentralController
{
protected:
	static MessageStack* a_message_stack;
	static CentralController* instance;
	std::mutex a_mutex;

	CentralController() = default;
	~CentralController() = default;

public:
	static CentralController* getInstance();
	void consumeMessages();
};

