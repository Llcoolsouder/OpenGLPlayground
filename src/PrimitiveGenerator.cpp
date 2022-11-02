#include "PrimitiveGenerator.h"

#include <glm/glm.hpp>
#include <vector>

namespace LSPrimitiveGenerator {

    std::shared_ptr<Mesh> Triangle() {
        std::vector<glm::vec3> vertices = { { -0.5f, -0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f },
		{ 0.0f, 0.5f, 0.0f } };

        std::vector<unsigned int> indices = {
            0, 1, 2
        };

        return std::make_shared<Mesh>(vertices, indices);
    }
}