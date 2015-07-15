#pragma once

#include <glm/glm.hpp>
#include "GLTexture.h"
#include "ResourceManager.h"

namespace Engine {
    class SpriteSheet {
    public:
        void init(std::string spriteSheetPath, glm::uvec2 spriteSheetDimensions) { m_texture = Engine::ResourceManager::getTexture(spriteSheetPath); m_dimensions = spriteSheetDimensions; }

        glm::vec4 getUVs(unsigned int index) const { return glm::vec4(index % m_dimensions.x * 1.0f / m_dimensions.x, index / m_dimensions.x * 1.0f / m_dimensions.y, 1.0f / m_dimensions.x, 1.0f / m_dimensions.y); }
        GLTexture getTexture() const { return m_texture; }
    private:
        GLTexture m_texture;
        glm::uvec2 m_dimensions;
    };
}
