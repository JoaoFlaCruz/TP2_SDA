#include "LogBuffer.h"

LogBuffer* LogBuffer::getInstance() {
    static LogBuffer instance;
    return &instance;
}

void LogBuffer::addMessage(const std::string& p_msg) {
    std::lock_guard<std::mutex> lock(a_mutex);
    if (a_messages.size() >= a_maxSize)
        a_messages.pop_front();
    a_messages.push_back(p_msg);
}

std::string LogBuffer::getAllMessages() {
    std::lock_guard<std::mutex> lock(a_mutex);
    std::string combined;
    for (const std::string& msg : a_messages) {
        combined += std::string(msg);
        combined += std::string("\r\n");
    }
    return combined;
}
