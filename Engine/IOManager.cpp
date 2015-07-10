#include <fstream>
#include "IOManager.h"
#include "Exception.h"

namespace Engine {
	bool IOManager::readFileToBuffer(std::string &filePath, std::vector<unsigned char> &buffer) {
		std::ifstream file(filePath, std::ios::binary);
		if (!file)
			throw Exception(filePath + " could not be opened!");

		file.seekg(0, std::ios::end);
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		fileSize -= file.tellg();

		buffer.resize(fileSize);
		file.read((char *)&(buffer[0]), fileSize);
		file.close();
		return true;
	}
}
