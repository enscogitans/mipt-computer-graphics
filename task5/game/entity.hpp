#pragma once

#include <glm/vec3.hpp>

#include <model/instance_interface.hpp>


namespace game {

/*
 * Represents game entities, e.g. enemies or fireballs
 */
class Entity : public model::Instance {
public:
    Entity(float collision_radius,
           const glm::vec3& center,
           const glm::mat4& rotation,
           const glm::vec3& speed = {0.0f, 0.0f, 0.0f});

    static bool IsOverlap(const Entity& lhs, const Entity& rhs);

    [[nodiscard]] glm::mat4 GetModelMatrix() const override;

    void UpdatePosition(float time_delta);

    [[nodiscard]] float GetDistance(const glm::vec3& to) const;

private:
    glm::vec3 center_;
    glm::mat4 rotation_;
    glm::vec3 speed_;

    float collision_radius_;
};

}  // namespace game
