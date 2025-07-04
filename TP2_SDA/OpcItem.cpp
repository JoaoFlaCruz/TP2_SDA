#include "OpcItem.h"

OpcItem::OpcItem(std::string p_item_name, IOPCItemMgt* p_iopc_item_mgt)
	: a_item_name(p_item_name),
	a_iopc_item_mgt(p_iopc_item_mgt)
{
	LogBuffer* log_buffer = LogBuffer::getInstance();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<OPCHANDLE> dist(10000000, 99999999);
	a_client_handle_item = dist(gen);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring w_item_name = converter.from_bytes(a_item_name);
	wchar_t* item_name = (wchar_t*) w_item_name.c_str();

	HRESULT hr;

	wchar_t sz_item_id[] = L"";
	OPCITEMDEF item_array[1] =
	{ {
			/*szAccessPath*/ sz_item_id,
			/*szItemID*/ item_name,
			/*bActive*/ TRUE,
			/*hClient*/ a_client_handle_item,
			/*dwBlobSize*/ 0,
			/*pBlob*/ NULL,
			/*vtRequestedDataType*/ VT,
			/*wReserved*/0
			} };

	//Add Result:
	OPCITEMRESULT* add_result = NULL;
	HRESULT* errors = NULL;

	// Add an Item to the previous Group:
	hr = a_iopc_item_mgt->AddItems(1, item_array, &add_result, &errors);
	if (hr != S_OK) {
		log_buffer->addMessage("Failed call to AddItems function. Error code = " + std::to_string(hr));
		return;
	}

	// Server handle for the added item:
	a_server_handle_item = add_result[0].hServer;

	// release memory allocated by the server:
	CoTaskMemFree(add_result->pBlob);

	CoTaskMemFree(add_result);
	add_result = NULL;

	CoTaskMemFree(errors);
	errors = NULL;

	log_buffer->addMessage("Item " + a_item_name + " adicionado com suscesso ao servidor OPC DA");
}

OpcItem::~OpcItem() {
	LogBuffer* log_buffer = LogBuffer::getInstance();

	OPCHANDLE server_array[1];
	server_array[0] = a_server_handle_item;

	HRESULT* errors;
	HRESULT hr = a_iopc_item_mgt->RemoveItems(1, server_array, &errors);
	_ASSERT(!hr);

	CoTaskMemFree(errors);
	errors = NULL;

	log_buffer->addMessage("Item " + a_item_name + " removido com suscesso ao servidor OPC DA");
}

void OpcItem::handleDataChange(const char* p_value, WORD p_quality, SYSTEMTIME p_timestamp) {
	LogBuffer* log_buffer = LogBuffer::getInstance();

	// Armazena o valor recebido como string
	a_item_value = p_value;

	// Converte qualidade para string hexadecimal
	std::stringstream ss_quality;
	ss_quality << "0x" << std::hex << std::uppercase << static_cast<int>(p_quality);
	a_item_quality = ss_quality.str();

	// Converte SYSTEMTIME para string (hh:mm:ss.mmm)
	std::ostringstream oss_time;
	oss_time << std::setfill('0')
		<< std::setw(2) << p_timestamp.wHour << ":"
		<< std::setw(2) << p_timestamp.wMinute << ":"
		<< std::setw(2) << p_timestamp.wSecond << "."
		<< std::setw(3) << p_timestamp.wMilliseconds;

	a_item_timestamp = oss_time.str();

	// Log final
	log_buffer->addMessage("ITEM [" + a_item_name + "] UPDATE: Valor [" + a_item_value +
		"], Qualidade: [" + a_item_quality +
		"] Timestamp: [" + a_item_timestamp + "]");
}

OPCHANDLE OpcItem::getClientHandle() {
	return a_client_handle_item;
}