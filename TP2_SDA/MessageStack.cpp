#include "MessageStack.h"
#include "MessageSocketClient.h"
#include "SocketMessage.h"

MessageStack* MessageStack::getInstance() {
    static MessageStack instance;
    return &instance;
}

bool MessageStack::insertSocketMessage(std::string p_message, MessageSocketClient* p_socket_server) {
    std::lock_guard<std::mutex> lock(a_mutex);

    if (isFull()) {
        return false;
    }

    SocketMessage message(p_message, p_socket_server);

    a_queue[a_tail] = std::make_unique<SocketMessage>(message);
    a_tail = (a_tail + 1) % MAX_SIZE;
    ++a_size;

    return true;
}

std::unique_ptr<SocketMessage> MessageStack::getNext() {
    std::lock_guard<std::mutex> lock(a_mutex);

    if (isEmpty()) {
        return nullptr;
    }

    std::unique_ptr<SocketMessage> result = std::move(a_queue[a_head]);
    a_head = (a_head + 1) % MAX_SIZE;
    --a_size;

    return result;
}

bool MessageStack::isEmpty() {
    return a_size <= 0;
}

bool MessageStack::isFull() {
    return a_size >= MAX_SIZE;
}

void MessageStack::clean() {
    std::lock_guard<std::mutex> lock(a_mutex);

    for (auto& msg : a_queue) {
        msg.reset();
    }

    a_head = 0;
    a_tail = 0;
    a_size = 0;
}
