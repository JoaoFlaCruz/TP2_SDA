#pragma once
#define WIN32_LEAN_AND_MEAN
#include "MessageStack.h"
#include "LogBuffer.h"
#include <mutex>
#include <chrono>
#include <thread>
#include "SocketMessage.h"

#include "OpcOperator.h"

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
	void handleMessage(std::unique_ptr<SocketMessage> p_message);
};

