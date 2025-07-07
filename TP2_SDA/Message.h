#pragma once
#include "StringMessage.h"
#include "CMessage_ACK.h"
#include "CRMessage_ACK.h"
#include "DPMessage.h"
#include "EDMessage.h"
#include "RDPMessage.h"

#include <string>
#include <vector>
#include <iostream>

class Message
{
protected:
	StringMessage* a_string_message;

	std::vector<std::string> clipMessage(const std::string& p_message);
public:
	Message(std::string p_message);
	~Message();

	bool send();
	std::string toString();
	StringMessage* getStringMessage();
	std::vector<std::string> getData();
};

