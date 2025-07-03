#include "OpcOperator.h"

OpcOperator::OpcOperator() {
	LogBuffer* log_buffer = LogBuffer::getInstance();

	log_buffer->addMessage("Inicializando o ambiente COM...");
	auto ignore_result = CoInitialize(NULL);

	std::string opc_server_prog_id = OPC_SERVER_PROG_ID;
	a_server = new OpcServer(opc_server_prog_id);

	a_server->addGroup("GrupoTeste1");
}

OpcOperator::~OpcOperator() {
	a_server->~OpcServer();
	CoUninitialize();
}

OpcOperator* OpcOperator::getInstance() {
	OpcOperator instance;
	return &instance;
}