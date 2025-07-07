#pragma once
#include "Message.h"
#include "MessageSocketClient.h"
#include "MessageStack.h"
#include "LogBuffer.h"

class MessageStack;

class SocketMessage :
    public Message
{
protected:
	MessageSocketClient* a_socket_server;

public:
	SocketMessage(std::string p_message, MessageSocketClient* p_socket_server);
	~SocketMessage();
	bool send();
};
