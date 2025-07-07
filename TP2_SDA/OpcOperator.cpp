#include "OpcOperator.h"

OpcOperator::OpcOperator() {
	a_thread = std::thread(&OpcOperator::runLoop, this);
}

OpcOperator::~OpcOperator() {
	{
		std::lock_guard<std::mutex> lock(a_mutex);
		a_running = false;
		a_cv.notify_all();
	}
	if (a_thread.joinable()) {
		a_thread.join();
	}
	delete a_server;
}

OpcOperator* OpcOperator::getInstance() {
	static OpcOperator instance;
	return &instance;
}

void OpcOperator::runLoop() {
	LogBuffer* log_buffer = LogBuffer::getInstance();

	log_buffer->addMessage("Thread OPCOperator iniciada");
	log_buffer->addMessage("Inicializando o ambiente COM...");
	auto ignore_result = CoInitializeEx(NULL, COINIT_MULTITHREADED);

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

	while (true) {
		std::unique_lock<std::mutex> lock(a_mutex);
		a_cv.wait(lock, [&]() { return !a_queue.empty() || !a_running; });

		if (!a_running && a_queue.empty()) break;

		auto cmd = a_queue.front();
		a_queue.pop();
		lock.unlock();

		cmd.action();
	}

	CoUninitialize();
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

void OpcOperator::enqueue(Command cmd) {
	{
		std::lock_guard<std::mutex> lock(a_mutex);
		a_queue.push(std::move(cmd));
	}
	a_cv.notify_one();
}

OpcServer* OpcOperator::getServer() {
	return a_server;
}