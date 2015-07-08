#include <string>
#include "GLTexture.h"
namespace Engine {
	class ImageLoader {
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}