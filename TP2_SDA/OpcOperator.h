#pragma once
#define WIN32_LEAN_AND_MEAN
#include <atlbase.h>
#include <iostream>
#include <ObjIdl.h>
#include <mutex>
#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>
#include <future>
#include <vector>

#include "SimpleOPCClient_V3/opcda.h"
#include "SimpleOPCClient_V3/opcerror.h"
#include "SimpleOPCClient_V3/SOCAdviseSink.h"
#include "SimpleOPCClient_V3/SOCDataCallback.h"
#include "SimpleOPCClient_V3/SOCWrapperFunctions.h"

#include "OpcConstants.h"
#include "OpcServer.h"
#include "LogBuffer.h"
#include "Config.h"

class OpcOperator {
public:
    struct Command {
        std::function<void()> action;
    };

private:
    OpcServer* a_server = nullptr;
    std::thread a_thread;
    std::mutex a_mutex;
    std::condition_variable a_cv;
    bool a_running = true;

    std::queue<Command> a_queue;

    OpcOperator();
    ~OpcOperator();

    void runLoop();

public:
    static OpcOperator* getInstance();
    void enqueue(Command cmd);
    void updateData(int p_op_number, int p_fab_recipe, float p_piece_type, float p_cel_id);
    std::vector<std::string> getData();
    OpcServer* getServer();
};

