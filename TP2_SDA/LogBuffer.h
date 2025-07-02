#pragma once
#include <deque>
#include <string>
#include <sstream>
#include <iostream>
#include <mutex>

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
