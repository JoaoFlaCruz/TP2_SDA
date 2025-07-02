#include "CentralController.h"

MessageStack* CentralController::a_message_stack = nullptr;

CentralController* CentralController::getInstance() {
    static CentralController instance;
    a_message_stack = MessageStack::getInstance();
    return &instance;
}

void CentralController::consumeMessages() {
    std::lock_guard<std::mutex> lock(a_mutex);
    LogBuffer* log_buffer = LogBuffer::getInstance();
    log_buffer->addMessage(std::string("Consumindo mensagens..."));

    while (true) {
        if (!a_message_stack->isEmpty()) {
            std::unique_ptr<Message> m = a_message_stack->getNext();
            log_buffer->addMessage(m->toString());
        }
    }
}