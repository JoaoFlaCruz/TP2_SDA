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

class LogBuffer {
private:
    std::deque<std::string> a_messages;
    const size_t a_maxSize = 20;
    std::mutex a_mutex;

    LogBuffer() = default;
    ~LogBuffer() = default;

public:
    static LogBuffer* getInstance();

    void addMessage(const std::string& p_msg);
    std::string getAllMessages();
};
