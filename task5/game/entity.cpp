#include "entity.hpp"

namespace game {

Entity::Entity(float collision_radius, const glm::vec3& center,
               const glm::mat4& rotation, const glm::vec3& speed)
        : collision_radius_(collision_radius)
        , rotation_(rotation)
        , center_(center)
        , speed_(speed)
{
}

glm::mat4 Entity::GetModelMatrix() const {
    return glm::translate(glm::mat4(1.0f), center_) * rotation_;
}

void Entity::UpdatePosition(float time_delta) {
    center_ += time_delta * speed_;
}

bool Entity::IsOverlap(const Entity& lhs, const Entity& rhs) {
    return glm::distance(lhs.center_, rhs.center_) < lhs.collision_radius_ + rhs.collision_radius_;
}

float Entity::GetDistance(const glm::vec3& to) const {
    float d = glm::distance(center_, to);
    return glm::max(0.0f, d - collision_radius_);
}

}  // namespace game
