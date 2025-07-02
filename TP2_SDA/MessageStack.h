#pragma once
#include "SocketMessage.h"
#include "LogBuffer.h";
#include <array>
#include <memory>
#include <mutex>

class MessageSocketServer;

class MessageStack {
private:
    static const size_t MAX_SIZE = 200;
    std::array<std::unique_ptr<Message>, MAX_SIZE> a_queue;
    size_t a_head = 0;
    size_t a_tail = 0;
    size_t a_size = 0;
    std::mutex a_mutex;

    MessageStack() = default;
    ~MessageStack() = default;

public:
    static MessageStack* getInstance();

    bool insertSocketMessage(std::string p_message, MessageSocketServer* p_socket_server);
    std::unique_ptr<Message> getNext();
    bool isEmpty();
    bool isFull();
    void clean();
};
