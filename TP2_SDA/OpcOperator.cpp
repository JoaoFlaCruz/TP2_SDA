#include "OpcOperator.h"

OpcOperator::OpcOperator() {
	LogBuffer* log_buffer = LogBuffer::getInstance();

	log_buffer->addMessage("Inicializando o ambiente COM...");
	auto ignore_result = CoInitialize(NULL);

	std::string opc_server_prog_id = OPC_SERVER_PROG_ID;
	a_server = new OpcServer(opc_server_prog_id);

	a_server->addGroup("GrupoLeituraAssincrona");
	OpcGroup* group = a_server->getGroup("GrupoLeituraAssincrona");
	group->addItem("Random.Int2");
	group->addItem("Random.Int4");
	group->addItem("Saw-toothed Waves.Real4");
	group->addItem("Triangle Waves.Real4");
	group->startCallback();

	a_server->addGroup("GrupoEscritaSincrona");
	group = a_server->getGroup("GrupoEscritaSincrona");
	group->addItem("Bucket Brigade.Int2");
	group->addItem("Bucket Brigade.Int4");
	group->addItem("Bucket Brigade.Real4");
	group->addItem("Bucket Brigade.Real8");
}

OpcOperator::~OpcOperator() {
	a_server->~OpcServer();
	CoUninitialize();
}

OpcOperator* OpcOperator::getInstance() {
	static OpcOperator instance;
	return &instance;
}

void OpcOperator::readMessages() {
	
}