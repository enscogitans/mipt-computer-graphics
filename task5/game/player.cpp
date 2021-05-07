#include "player.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace game {

Player::Player(const glm::vec3& view_point, const glm::vec3& view_direction, const glm::vec3& up_direction)
        : view_point_(view_point)
        , view_direction_(view_direction)
        , up_direction_(up_direction)
        , prev_shoot_time_(0.0)
{
}

glm::mat4 Player::GetViewMatrix() const {
    return glm::lookAt(view_point_, view_direction_, up_direction_);
}

std::optional<Entity> Player::Shoot(float fireball_radius, float fireball_speed, double shoot_cooldown) {
    double time = glfwGetTime();
    if (time - prev_shoot_time_ < shoot_cooldown) {
        return std::nullopt;
    }
    prev_shoot_time_ = time;
    glm::vec3 eye_vector_norm = glm::normalize(view_direction_ - view_point_);
    glm::vec3 fireball_pos = view_point_ + 2 * fireball_radius * eye_vector_norm;
    return Entity(fireball_radius, fireball_pos, glm::mat4(1.0f), fireball_speed * eye_vector_norm);
}

glm::vec3 Player::GetPosition() const {
    return view_point_;
}

void Player::MoveViewDirection(float horizontal_angle_delta, float vertical_angle_delta) {
    glm::vec3 eye_vector = view_direction_ - view_point_;

    // Disallow vertical "flips". Don't move camera up/down if player already looks maximally up/down
    float curr_angle = glm::acos(glm::dot(glm::normalize(eye_vector), glm::normalize(up_direction_)));
    vertical_angle_delta = glm::min(vertical_angle_delta, curr_angle);
    vertical_angle_delta = glm::max(vertical_angle_delta, curr_angle - glm::pi<float>());

    glm::mat4 transform = glm::rotate(glm::mat4(1.0f), horizontal_angle_delta, up_direction_);
    transform = glm::rotate(transform, vertical_angle_delta, glm::cross(eye_vector, up_direction_));

    view_direction_ = view_point_ + glm::make_vec3(transform * glm::make_vec4(eye_vector));
}

}  // namespace game
