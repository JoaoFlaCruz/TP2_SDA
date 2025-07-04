#pragma once
#define WIN32_LEAN_AND_MEAN
#include "LogBuffer.h"
#include <array>
#include <memory>
#include <mutex>
#include "Message.h"

class MessageSocketServer;
class SocketMessage;

class MessageStack {
private:
    static const size_t MAX_SIZE = 200;
    std::array<std::unique_ptr<SocketMessage>, MAX_SIZE> a_queue;
    size_t a_head = 0;
    size_t a_tail = 0;
    size_t a_size = 0;
    std::mutex a_mutex;

    MessageStack() = default;
    ~MessageStack() = default;

public:
    static MessageStack* getInstance();

    bool insertSocketMessage(std::string p_message, MessageSocketServer* p_socket_server);
    std::unique_ptr<SocketMessage> getNext();
    bool isEmpty();
    bool isFull();
    void clean();
};
