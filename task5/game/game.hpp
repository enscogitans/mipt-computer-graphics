#pragma once

#include <random>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glfw_wrapper/session.hpp>
#include <model/instancing_model.hpp>
#include <model/instance_interface.hpp>
#include <common/text.hpp>

#include "entity.hpp"
#include "player.hpp"


namespace game {

class Game {
public:
    explicit Game(const std::shared_ptr<gl::Session>& session);

    void Run();

private:  // Game parameters
    static constexpr int kWindowWidth = 1280;
    static constexpr int kWindowHeight = 720;
    const std::string kWindowTitle = "Task 5";

    const float kMouseSensitivity = 0.006f;

    static constexpr float kFov = glm::radians(50.0f);
    static constexpr float kAspect = 16.0f / 9.0f;
    static constexpr float kZNear = 0.1f;
    static constexpr float kZFar = 50.0f;
    const glm::mat4 kProjection = glm::perspective(kFov, kAspect, kZNear, kZFar);

    static constexpr float kWorldRadius = 100.0f;
    static_assert(kZFar < kWorldRadius, "Size of the world is less than the distance player can see");

    const std::filesystem::path kEnemyVertexShaderPath = "resources/dodecahedron/vertex.shader";
    const std::filesystem::path kEnemyFragmentShaderPath = "resources/dodecahedron/fragment.shader";
    static constexpr float kEnemyRadius = 1.0f;
    static constexpr float kEnemySpeed = 5.0f;

    const std::filesystem::path kFireballModelPath = "resources/fireball/fireball.fbx";
    const std::filesystem::path kFireballTexturePath = "resources/fireball/texture.bmp";
    const std::filesystem::path kFireballVertexShaderPath = "resources/fireball/vertex.shader";
    const std::filesystem::path kFireballFragmentShaderPath = "resources/fireball/fragment.shader";
    static constexpr float kFireballRadius = 0.1f;
    static constexpr float kFireballSpeed = 5.0f;

    static constexpr float kEnemyGenerationTimeDelta = 2.0f;  // 2 sec
    static constexpr float kEnemyGenerationMinDistance = 15.0f;
    static constexpr float kEnemyGenerationMaxDistance = 40.0f;

    static constexpr float kPlayerShootCooldown = 1.0f;  // 1 sec
    static constexpr glm::vec3 kPlayerViewPoint = {0, 0, 0};
    static constexpr glm::vec3 kPlayerViewDirection = {0, 0, 1};

    const std::filesystem::path kFontPath = "resources/font/holstein.dds";
    const std::filesystem::path kFontVertexShaderPath = "resources/font/vertex.shader";
    const std::filesystem::path kFontFragmentShaderPath = "resources/font/fragment.shader";
    static constexpr int kFontSize = 25;
    static constexpr int kFontLeading = kFontSize * 3 / 2;

    static constexpr int kHudPositionX = 10;
    static constexpr int kHudPositionY = kWindowHeight - 30;

private:
    std::shared_ptr<gl::Session> session_;
    std::unique_ptr<gl::Window> window_;

    Player player_;

    model::InstancingModel enemy_model_;
    std::vector<Entity> enemy_entities_;

    model::InstancingModel fireball_model_;
    std::vector<Entity> fireball_entities_;

    std::mt19937 random_generator_;

    int enemies_destroyed_ = 0;
    int enemies_missed_ = 0;
    utils::TextDrawer text_drawer_;

private:
    void DrawHud();

    void UpdateEntities(float time_delta);

    void GenerateEnemy();

    void RegisterControlCallbacks();

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void MousePosCallback(GLFWwindow* window, double x, double y);

    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};

}  // namespace game
