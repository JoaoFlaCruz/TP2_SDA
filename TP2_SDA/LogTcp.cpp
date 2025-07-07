#include "LogTcp.h"

LogTcp* LogTcp::getInstance() {
    static LogTcp instance;
    return &instance;
}

void LogTcp::addMessage(const std::string& p_msg) {
    std::lock_guard<std::mutex> lock(a_mutex);

    auto now = std::chrono::system_clock::now();
    std::time_t t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now;
    localtime_s(&tm_now, &t_now);

    // Obtém o ID da thread
    std::ostringstream oss;
    oss << "[" << std::put_time(&tm_now, "%H:%M:%S") << "][TID " << std::this_thread::get_id() << "] " << p_msg;

    if (a_messages.size() >= a_maxSize)
        a_messages.pop_front();
    a_messages.push_back(oss.str());

    Update::getInstance()->triggerMainWindow();
}


std::string LogTcp::getAllMessages() {
    std::lock_guard<std::mutex> lock(a_mutex);
    std::string combined;
    for (auto it = a_messages.rbegin(); it != a_messages.rend(); ++it) {
        combined += *it + "\r\n";
    }
    return combined;
}