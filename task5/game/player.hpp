#pragma once

#include <memory>
#include <optional>

#include <glm/vec3.hpp>

#include "entity.hpp"


namespace game {

class Player {
public:
    Player(const glm::vec3& view_point, const glm::vec3& view_direction, const glm::vec3& up_direction = {0, 1, 0});

    std::optional<Entity> Shoot(float fireball_radius, float fireball_speed, double shoot_cooldown);

    [[nodiscard]] glm::mat4 GetViewMatrix() const;

    [[nodiscard]] glm::vec3 GetPosition() const;

    void MoveViewDirection(float horizontal_angle_delta, float vertical_angle_delta);

private:
    glm::vec3 view_point_;
    glm::vec3 view_direction_;
    glm::vec3 up_direction_;

    double prev_shoot_time_;
};

}  // namespace game
