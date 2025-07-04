#include "EndMessage.h"

EndMessage::EndMessage() : StringMessage(-1) {}

StringMessage* EndMessage::buildSelf(const std::vector<std::string>& values) {
	return (StringMessage*) new EndMessage();
}

std::string EndMessage::getMessage() {
	return std::string("end");
}

StringMessage* EndMessage::getResponse() {
	return nullptr;
}