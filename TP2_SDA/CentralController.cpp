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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (!a_message_stack->isEmpty()) {
            std::lock_guard<std::mutex> lock(a_mutex);
            std::unique_ptr<Message> m = a_message_stack->getNext();
            log_buffer->addMessage(m->toString());
        }
    }
}