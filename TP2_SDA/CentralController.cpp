#include "CentralController.h"

MessageStack* CentralController::a_message_stack = nullptr;

CentralController* CentralController::getInstance() {
    static CentralController instance;
    return &instance;
}

CentralController::CentralController() {
    a_message_stack = MessageStack::getInstance();
}


void CentralController::consumeMessages() {
    LogBuffer* log_buffer = LogBuffer::getInstance();

    {
        std::lock_guard<std::mutex> lock(a_mutex);
        log_buffer->addMessage(std::string("Consumindo mensagens..."));
    }

    while (true) {
        if (!a_message_stack->isEmpty()) {
            std::lock_guard<std::mutex> lock(a_mutex);
            std::unique_ptr<SocketMessage> m = a_message_stack->getNext();
            log_buffer->addMessage(m->toString());
            handleMessage(std::move(m));
        }
    }
}

void CentralController::handleMessage(std::unique_ptr<SocketMessage> p_message) {
    p_message->send();
}
