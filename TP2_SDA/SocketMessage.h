#pragma once
#include "Message.h"
#include "MessageSocketServer.h"
#include "LogBuffer.h";

class SocketMessage :
    public Message
{
protected:
	MessageSocketServer* a_socket_server;

public:
	SocketMessage(std::string p_message, MessageSocketServer* p_socket_server);
	~SocketMessage();
};
