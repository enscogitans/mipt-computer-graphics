#pragma once

#include <glm/gtc/type_ptr.hpp>

namespace model {

class Instance {
public:
    [[nodiscard]] virtual glm::mat4 GetModelMatrix() const = 0;
    virtual ~Instance() = default;
};

}  // namespace model
