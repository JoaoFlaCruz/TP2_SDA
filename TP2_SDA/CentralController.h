#pragma once

#include "MessageStack.h"
#include "LogBuffer.h"
#include <mutex>
#include <chrono>
#include <thread>

class CentralController
{
protected:
	static MessageStack* a_message_stack;
	static CentralController* instance;
	std::mutex a_mutex;

	CentralController();
	~CentralController() = default;

public:
	static CentralController* getInstance();
	void consumeMessages();
	void handleMessages(Message p_message);
};

