#pragma once
#define WIN32_LEAN_AND_MEAN
#include <deque>
#include <string>
#include <sstream>
#include <iostream>
#include <mutex>
#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>

#include "Update.h"
#include "Config.h"

class LogOpc
{
private:
    std::deque<std::string> a_messages;
    const size_t a_maxSize = OPC_BUFFER_SIZE;
    std::mutex a_mutex;

    LogOpc() = default;
    ~LogOpc() = default;
public:
    static LogOpc* getInstance();

    void addMessage(const std::string& p_msg);
    std::string getAllMessages();
};

