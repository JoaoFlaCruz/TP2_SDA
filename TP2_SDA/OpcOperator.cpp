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

void OpcOperator::updateData(int p_op_number, int p_fab_recipe, float p_piece_type, float p_cel_id) {
	std::lock_guard<std::mutex> lock(a_mutex);
	OpcGroup* group = a_server->getGroup("GrupoEscritaSincrona");
	std::string op_number = std::to_string(p_op_number);
	std::string fab_recipe = std::to_string(p_fab_recipe);
	std::string piece_type = std::to_string(p_piece_type);
	std::string cel_id = std::to_string(p_cel_id);

	OpcItem* item = group->getItem("Bucket Brigade.Int2");
	item->writeValue(op_number);
	item = group->getItem("Bucket Brigade.Int4");
	item->writeValue(fab_recipe);
	item = group->getItem("Bucket Brigade.Real4");
	item->writeValue(piece_type);
	item = group->getItem("Bucket Brigade.Real8");
	item->writeValue(cel_id);
}

std::vector<std::string> OpcOperator::getData() {
	std::vector<std::string> data;

	OpcGroup* group = a_server->getGroup("GrupoLeituraAssincrona");
	data.push_back(group->getItem("Random.Int2")->getValue());
	data.push_back(group->getItem("Random.Int4")->getValue());
	data.push_back(group->getItem("Saw-toothed Waves.Real4")->getValue());
	data.push_back(group->getItem("Triangle Waves.Real4")->getValue());

	return data;
}
