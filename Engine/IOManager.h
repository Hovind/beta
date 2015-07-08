#include <string>
#include <vector>

namespace Engine {
	class IOManager {
	public:
		static bool readFileToBuffer(std::string &filePath, std::vector<unsigned char> &buffer);
};
}